#include "BackpackDetector.h"
//using MOG2 method
const std::string BackpackDetector::BG_MOG_METHOD = "mog";
//using KNN method
const std::string BackpackDetector::BG_KNN_METHOD = "knn";

BackpackDetector::BackpackDetector()
{
    MEMORY("BackpackDetector created");

    UI::pirintID = -1;

    ConfigManager cfg = ConfigManager::getConfigManager();
    cv::namedWindow(ConfigManager::VIEW_FINAL_RESULT, 1);

    cv::setMouseCallback(ConfigManager::VIEW_FINAL_RESULT, UI::callbackMouse, NULL);

    _bgLong = cv::createBackgroundSubtractorMOG2(cfg.get<int>
              (cfg.BD_BG_MOG_HISTORY), cfg.get<int>(cfg.BD_BG_MOG_MIXTURES),
              cfg.get<bool>(cfg.BD_BG_MOG_SHADOW));
    //setup MOG method
    if(cfg.get<std::string>(cfg.BD_BG_METHOD) ==BG_MOG_METHOD) {
        _mog2 = cv::createBackgroundSubtractorMOG2(
                    cfg.get<int>(cfg.BD_MOG_HISTORY),cfg.get<int>(cfg.BD_MOG_MIXTURES),
                    cfg.get<bool>(cfg.BD_MOG_SHADOW));

    }
    //setup KNN method
    if(cfg.get<std::string>(cfg.BD_BG_METHOD) == BG_KNN_METHOD) {
        _mog2 = cv::createBackgroundSubtractorKNN(
                    cfg.get<int>(cfg.BD_KNN_HISTORY),cfg.get<int>(cfg.BD_KNN_MIXTURES),
                    cfg.get<bool>(cfg.BD_KNN_SHADOW));

    }
}

BackpackDetector::~BackpackDetector()
{
    MEMORY("BackpackDetector destroyed");
}

void BackpackDetector::update(cv::Mat ref)
{
    DataManager &dm = DataManager::getDataManager();
    ConfigManager cfg = ConfigManager::getConfigManager();
    cv::Mat tmp,cbg;
    _bgLong->apply(ref, tmp);
    _bgLong->getBackgroundImage(DataManager::getDataManager().cBG);

    for(unsigned long it = 0;it<dm.backpacks.size();it++){
        
        if(dm.backpacks[it].wasStable)
        dm.backpacks[it].patch(DataManager::getDataManager().cBG); 


    }
    dm.patchBuffer.addFrame(DataManager::getDataManager().cBG);

}

void BackpackDetector::detect(cv::Mat ref)
{
    bgDiffMethod(ref);
}

bool BackpackDetector::checkDiff(cv::Mat diff)
{
    int count_white = 0;
    for( int y = 0; y < diff.rows; y++  ) {
        for( int x = 0; x < diff.cols; x++  ) {
            if ( diff.at<uchar>(y,x) == 255  ) {
                count_white++;
            }
        }
    }
    if(count_white / (double)(diff.cols*diff.rows) >
            ConfigManager::getConfigManager().get<double>(ConfigManager::BD_DIFF_TRESH) ) {
        return true;
    }

    return false;
}



void BackpackDetector::bgDiffMethod(cv::Mat ref)
{

    DataManager &dm = DataManager::getDataManager();
    ConfigManager &cfg = ConfigManager::getConfigManager();
    cv::Mat estF, estBg;

    _mog2->apply(ref,estF);
    _mog2->getBackgroundImage(estBg);

    display(ConfigManager::VIEW_BD_FOREGROUND, estF);
    display(ConfigManager::VIEW_BD_BACKGROUND, estBg);


    cv::Mat out;
    dm.addFrame(estBg);
    if(dm.isFull()) {
        cv::Mat sum;
        //diff
        cv::absdiff(dm.get(0),dm.cBG,out);
        //remove noise
        cv::threshold(out,out,cfg.get<int>(cfg.BD_DM_TRESH),255,0);
        int er = cfg.get<int>(cfg.BD_DM_ERODE);
        int di = cfg.get<int>(cfg.BD_DM_DILATE);

        cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1,
                               2*er+1  ), cv::Point( er, er  )  );
        cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1,
                                2*di+1  ), cv::Point( di, di  )  );
        cv::erode(out,out,erodeElement);
        cv::dilate(out,out,dilateElement);

        out.copyTo(sum);
        //agregate rest of the framebuffer
        for(int i =1; i< dm.getSize(); i++) {
            cv::absdiff(dm.get(i),dm.cBG,out);
            cv::threshold(out,out,cfg.get<int>(cfg.BD_DM_TRESH),255,0);

            cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1,
                                   2*er+1  ), cv::Point( er, er  )  );
            cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1,
                                    2*di+1  ), cv::Point( di, di  )  );
            cv::erode(out,out,erodeElement);
            cv::dilate(out,out,dilateElement);
            //agregation
            cv::bitwise_and(sum,out,sum);

        }

        display(ConfigManager::VIEW_BD_LONG_BG, dm.cBG);
        display(ConfigManager::VIEW_BD_DIFF_RESULT, sum);

        cv::Mat contoursMat;
        out.copyTo(contoursMat);
        cv::Mat tmp;
        ref.copyTo(tmp);

        //contours detection
        std::vector<cv::Vec4i> hierarchy;
        std::vector<std::vector<cv::Point> > contours;
        findContours( contoursMat, contours, hierarchy, CV_RETR_EXTERNAL,
                      CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)  );
        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<std::vector<cv::Point> > contoursPoly(contours.size());

        for( unsigned long i = 0; i< contours.size(); i++  ) {
            //get rects from contours
            approxPolyDP(cv::Mat(contours[i]),contoursPoly[i],10,false);
            boundRect[i] = boundingRect(cv::Mat(contoursPoly[i]));

            bool ok =true;
            //remove duplicates and overlapping rects;
            for(unsigned long j =0; j< dm.backpacks.size(); j++) {
                if(utils::detect::checkOverlapping<int>( boundRect[i],dm.backpacks[j].getRoi(),cfg.get<double>(ConfigManager::BD_OVERLAP_TRESH),dm.backpacks[j].destoyed)) {
                    ok=false;
                    break;
                }
                if(utils::detect::checkOverlapping<int>( dm.backpacks[j].getRoi(),boundRect[i],cfg.get<double>(ConfigManager::BD_OVERLAP_TRESH),dm.backpacks[j].destoyed)) {
                    ok=false;
                    break;
                }


            }
            //add only unique
            if(ok) {
                //create backpack
                Backpack backpack(boundRect[i], dm.cBG(boundRect[i]),dm.cBG(boundRect[i]),dm.patchBuffer.getLast()(boundRect[i]),
                        cfg.get<int>(cfg.BD_BACKPACK_LIFE), cfg.get<int>(cfg.BD_COUNT_DOWN)
                        );
                //take snapshot
                backpack.takeSnapshot(cfg.get<int>(ConfigManager::BD_SNAPSHOT_SIZE), dm.people,
                                      cfg.get<double>(ConfigManager::BD_SNAPSHOT_TRESH),UI::FINAL, cfg.get<std::string>(cfg.RUNTIME));
                //save
                dm.backpacks.push_back(backpack);

            }

        }
        //repeat diff agregation for existing backpacks for calculate confidance that detected backpack is actually backpack
        for(unsigned long j =0; j< dm.backpacks.size(); j++) {

            cv::Mat sum;

            cv::absdiff(dm.get(0)(dm.backpacks[j].getRoi()),dm.backpacks[j].getBase(),out);
            cv::threshold(out,out,cfg.get<int>(ConfigManager::BD_DM_TRESH),255,0);

            cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1,
                                   2*er+1  ), cv::Point( er, er  )  );
            cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1,
                                    2*di+1  ), cv::Point( di, di  )  );
            cv::erode(out,out,erodeElement);
            cv::dilate(out,out,dilateElement);

            out.copyTo(sum);

            for(int i =1; i< dm.getSize(); i++) {
                cv::absdiff(dm.get(i)(dm.backpacks[j].getRoi()),dm.backpacks[j].getBase(),out);
                cv::threshold(out,out,cfg.get<int>(ConfigManager::BD_DM_TRESH),255,0);

                cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1,
                                       2*er+1  ), cv::Point( er, er  )  );
                cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1,
                                        2*di+1  ), cv::Point( di, di  )  );
                cv::erode(out,out,erodeElement);
                cv::dilate(out,out,dilateElement);
                cv::bitwise_and(sum,out,sum);

            }


            if(checkDiff(sum)) {
                dm.backpacks[j].incConfidence(1);
            } else {
                //punish backpack with low difference factor
                dm.backpacks[j].incConfidence(cfg.get<int>(cfg.BD_UNSTABLE_COST));

                // different cost level fot stable backpacks
                if(dm.backpacks[j]._stable > cfg.get<int>(cfg.BD_STABLE_TRESH))
                    dm.backpacks[j].incConfidence(cfg.get<int>(cfg.BD_STABLE_COST));

            }


            dm.backpacks[j].incChecks();
            if(dm.backpacks[j].getChecks()>cfg.get<int>(cfg.BD_CHECKS_TRESH)) {
                if(dm.backpacks[j].getConfidence()/(double)dm.backpacks[j].getChecks() <
                        cfg.get<double>(cfg.BD_CONFIDANCE)) {

                    //if confidence/(number of checks) is to low then remove backpack, because it is not realy a backpack
                    if(dm.backpacks[j].wasStable){
                        dm.backpacks[j].destoyed = true;
                        continue;
                    }
                    dm.backpacks.erase(dm.backpacks.begin()+j);
                    continue;


                } else {
                    if(dm.backpacks[j]._stableConfidance % 10 == 0)
                    dm.backpacks[j].setNewBase(dm.cBG(dm.backpacks[j].getRoi()));
                    //else increase stable level which determines real backpacks
                    dm.backpacks[j].incStableConfidance(cfg.get<int>
                                                        (ConfigManager::BD_MAIN_CONFIDANCE));
                    dm.backpacks[j]._stable++;
                }
            }

            //draw only stable
            if(dm.backpacks[j]._stableConfidance / 254.0 * 100 > cfg.get<int>(cfg.BD_STABLE_CONF_TRESH)) {
/*
                cv::imwrite(cfg.get<std::string>(cfg.RUNTIME)+"/"+utils::str::to_string<int>(dm.backpacks[j].getID())+".png", ref(dm.backpacks[j].getRoi()));

   for(unsigned long t=0; t<dm.backpacks[j]._people.size(); t++){
            cv::imwrite(cfg.get<std::string>(cfg.RUNTIME)+"/"+utils::str::to_string<int>(dm.backpacks[j].getID())+"-"+utils::str::to_string<int>(dm.people[dm.backpacks[j]._people[t]].getID())+".png", ref(dm.people[dm.backpacks[j]._people[t]]._roid));
    }
  */

                if(!dm.backpacks[j].wasStable){
                SESSION(
                        "Backpack: Detected! ID: " + utils::str::to_string<int>(dm.backpacks[j].getID())
                       );
                }
                dm.backpacks[j].status();

                cv::rectangle(tmp, dm.backpacks[j].getRoi().tl(), dm.backpacks[j].getRoi().br(),
                              dm.backpacks[j].getColor(), 2,8,0);
                cv::rectangle(UI::FINAL, dm.backpacks[j].getRoi().tl(),
                              dm.backpacks[j].getRoi().br(), dm.backpacks[j].getColor(), 2,8,0);
                dm.stableBackpacks.insert(std::pair<int, Backpack>(dm.backpacks[j].getID(), dm.backpacks[j]));
                dm.backpacks[j].wasStable = true;
               // INFO(utils::str::to_string<int>(dm.backpacks[j].getID())+":"+ utils::str::to_string<int>(dm.backpacks[j].getChecks())+":"+utils::str::to_string<int>(dm.backpacks[j]._stableConfidance));
                //print ID
                if(cfg.get<bool>(cfg.BD_ID_TEXT)) {
                    cv::putText(tmp,utils::str::to_string<int>(dm.backpacks[j].getID()),
                                cv::Point(dm.backpacks[j].getRoi().x,dm.backpacks[j].getRoi().y),
                                cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,cv::LINE_AA);
                    cv::putText(UI::FINAL,utils::str::to_string<int>(dm.backpacks[j].getID()),
                                cv::Point(dm.backpacks[j].getRoi().x,dm.backpacks[j].getRoi().y),
                                cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,cv::LINE_AA);
            }
                }

//print people binded with selected backpack
        if(UI::pirintID==dm.backpacks[j].getID()) {
            for(unsigned long t = 0 ;
                    t < DataManager::getDataManager().backpacks[j]._people.size(); t++) {
                cv::Rect2d roi =
                    DataManager::getDataManager().people[DataManager::getDataManager().backpacks[j]._people[t]]._roid;
                cv::rectangle(UI::FINAL, roi.tl(), roi.br(), cv::Scalar(255,0,0), 2,8,0);
                    cv::putText(UI::FINAL,utils::str::to_string<int>(dm.backpacks[j]._people[t]),
                                cv::Point(roi.x,roi.y),
                                cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,cv::LINE_AA);

 

            }
        }

        }
        
         cv::putText(UI::FINAL,utils::str::to_string<long>(TimeManager::getTimeManager().time()),
                                cv::Point(0,12),
                                cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(255,0,0),2,cv::LINE_AA);
    
        display(ConfigManager::VIEW_FINAL_RESULT, UI::FINAL);
        display(ConfigManager::VIEW_BD_RESULT, tmp);
    }

}


