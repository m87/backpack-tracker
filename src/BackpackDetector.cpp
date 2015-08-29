#include "BackpackDetector.h"

const std::string BackpackDetector::BG_MOG_METHOD = "mog";
const std::string BackpackDetector::BG_KNN_METHOD = "knn";

cv::Mat BackpackDetector::FINAL, BackpackDetector::FINAL_CP;
int BackpackDetector::pirintID;



void BackpackDetector::callbackMouse(int event, int x, int y, int flags, void *userdata){
        if  ( event == EVENT_LBUTTONDOWN  )
        {
            for(unsigned long t = 0; t <  DataManager::getDataManager().backpacks.size(); t++){
               if( x > DataManager::getDataManager().backpacks[t].getRoi().x && 
            y > DataManager::getDataManager().backpacks[t].getRoi().y && 
x < DataManager::getDataManager().backpacks[t].getRoi().x +DataManager::getDataManager().backpacks[t].getRoi().width && 
x < DataManager::getDataManager().backpacks[t].getRoi().x  + DataManager::getDataManager().backpacks[t].getRoi().height

){
                   BackpackDetector::pirintID = t;
                   INFO(DataManager::getDataManager().backpacks[t].getID());
                   break;
               }
                       }
        


        }
        if  ( event == EVENT_RBUTTONDOWN  )
        {
            BackpackDetector::pirintID = -1;
            return; 
        }

}




BackpackDetector::BackpackDetector() {
    MEMORY("BackpackDetector created");

    BackpackDetector::pirintID = -1;

    ConfigManager cfg = ConfigManager::getConfigManager();
    cv::namedWindow(ConfigManager::VIEW_FINAL_RESULT, 1);

    cv::setMouseCallback(ConfigManager::VIEW_FINAL_RESULT, BackpackDetector::callbackMouse, NULL);

    _bgLong = cv::createBackgroundSubtractorMOG2(cfg.get<int>(cfg.BD_BG_MOG_HISTORY), cfg.get<int>(cfg.BD_BG_MOG_MIXTURES), cfg.get<bool>(cfg.BD_BG_MOG_SHADOW));

    if(cfg.get<std::string>(cfg.BD_BG_METHOD) == BG_MOG_METHOD) {
        _mog2 = cv::createBackgroundSubtractorMOG2(
                    cfg.get<int>(cfg.BD_MOG_HISTORY),cfg.get<int>(cfg.BD_MOG_MIXTURES),cfg.get<bool>(cfg.BD_MOG_SHADOW)              );

    }
    if(cfg.get<std::string>(cfg.BD_BG_METHOD) == BG_KNN_METHOD) {
        _mog2 = cv::createBackgroundSubtractorKNN(
                    cfg.get<int>(cfg.BD_KNN_HISTORY),cfg.get<int>(cfg.BD_KNN_MIXTURES),cfg.get<bool>(cfg.BD_KNN_SHADOW)              );

    }
}

BackpackDetector::~BackpackDetector() {
    MEMORY("BackpackDetector destroyed");
}

void BackpackDetector::update(cv::Mat ref) {
    cv::Mat tmp;
    _bgLong->apply(ref, tmp);
    _bgLong->getBackgroundImage(DataManager::getDataManager().cBG);
}


void BackpackDetector::detect(cv::Mat ref) {
    bgDiffMethod(ref);
}

bool checkDiff(cv::Mat diff) {
    int count_white = 0;
    for( int y = 0; y < diff.rows; y++  ) {
        for( int x = 0; x < diff.cols; x++  ) {
            if ( diff.at<uchar>(y,x) == 255  ) {
                count_white++;
            }
        }
    }
    if(count_white / (double)(diff.cols*diff.rows) > ConfigManager::getConfigManager().get<double>(ConfigManager::BD_DIFF_TRESH) )
    {
        return true;
    }

    return false;
}

bool checkOverlapping(cv::Rect A, cv::Rect B) {
    cv::Rect inter = A & B;
    if(inter.width > A.width * ConfigManager::getConfigManager().get<double>(ConfigManager::BD_OVERLAP_TRESH)  || inter.height > A.height *ConfigManager::getConfigManager().get<double>(ConfigManager::BD_OVERLAP_TRESH))
    {
        return true;

    }
    return false;

}

bool checkOverlapping2(cv::Rect A, cv::Rect B) {
    cv::Rect inter = A & B;
    if(inter.width > B.width * ConfigManager::getConfigManager().get<double>(ConfigManager::BD_OVERLAP_TRESH)  || inter.height > B.height * ConfigManager::getConfigManager().get<double>(ConfigManager::BD_OVERLAP_TRESH))
    {
        return true;
    }
    return false;

}




void BackpackDetector::bgDiffMethod(cv::Mat ref) {

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
        cv::absdiff(dm.get(0),dm.cBG,out);
        cv::threshold(out,out,cfg.get<int>(cfg.BD_DM_TRESH),255,0);
        int er = cfg.get<int>(cfg.BD_DM_ERODE);
        int di = cfg.get<int>(cfg.BD_DM_DILATE);

        cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1, 2*er+1  ), cv::Point( er, er  )  );
        cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1, 2*di+1  ), cv::Point( di, di  )  );
        cv::erode(out,out,erodeElement);
        cv::dilate(out,out,dilateElement);

        out.copyTo(sum);

        for(int i =1; i< dm.getSize(); i++) {
            cv::absdiff(dm.get(i),dm.cBG,out);
            cv::threshold(out,out,cfg.get<int>(cfg.BD_DM_TRESH),255,0);

            cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1, 2*er+1  ), cv::Point( er, er  )  );
            cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1, 2*di+1  ), cv::Point( di, di  )  );
            cv::erode(out,out,erodeElement);
            cv::dilate(out,out,dilateElement);
            cv::bitwise_and(sum,out,sum);

        }

        display(ConfigManager::VIEW_BD_LONG_BG, dm.cBG);
        display(ConfigManager::VIEW_BD_DIFF_RESULT, sum);

        cv::Mat contoursMat;
        out.copyTo(contoursMat);
        cv::Mat tmp;
        ref.copyTo(tmp);

        std::vector<cv::Vec4i> hierarchy;
        std::vector<std::vector<cv::Point> > contours;
        findContours( contoursMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)  );
        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<std::vector<cv::Point> > contoursPoly(contours.size());

        for( unsigned long i = 0; i< contours.size(); i++  )
        {
            approxPolyDP(Mat(contours[i]),contoursPoly[i],10,false);
            boundRect[i] = boundingRect(Mat(contoursPoly[i]));

            bool ok =true;

            for(unsigned long j =0; j< dm.backpacks.size(); j++) {
                if(checkOverlapping(dm.backpacks[j].getRoi(), boundRect[i])) {
                    ok=false;
                    break;
                }
                if(checkOverlapping2(dm.backpacks[j].getRoi(), boundRect[i])) {
                    ok=false;
                    break;
                }


            }

            if(ok) {
                Backpack backpack(boundRect[i], dm.cBG(boundRect[i]),dm.cBG(boundRect[i]));
                backpack.takeSnapshot(cfg.get<int>(ConfigManager::BD_SNAPSHOT_SIZE), dm.people);
                dm.backpacks.push_back(backpack);

            }

        }
        for(unsigned long j =0; j< dm.backpacks.size(); j++) {


            cv::Mat sum;

            cv::absdiff(dm.get(0)(dm.backpacks[j].getRoi()),dm.backpacks[j].getBase(),out);
            cv::threshold(out,out,cfg.get<int>(ConfigManager::BD_DM_TRESH),255,0);

            cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1, 2*er+1  ), cv::Point( er, er  )  );
            cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1, 2*di+1  ), cv::Point( di, di  )  );
            cv::erode(out,out,erodeElement);
            cv::dilate(out,out,dilateElement);

            out.copyTo(sum);

            for(int i =1; i< dm.getSize(); i++) {
                cv::absdiff(dm.get(i)(dm.backpacks[j].getRoi()),dm.backpacks[j].getBase(),out);
                cv::threshold(out,out,cfg.get<int>(ConfigManager::BD_DM_TRESH),255,0);

                cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*er + 1, 2*er+1  ), cv::Point( er, er  )  );
                cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*di + 1, 2*di+1  ), cv::Point( di, di  )  );
                cv::erode(out,out,erodeElement);
                cv::dilate(out,out,dilateElement);
                cv::bitwise_and(sum,out,sum);

            }


            if(checkDiff(sum)) {
                dm.backpacks[j].incConfidence(1);
            } else {

                dm.backpacks[j].incConfidence(cfg.get<int>(cfg.BD_UNSTABLE_COST));

                if(dm.backpacks[j]._stable > cfg.get<int>(cfg.BD_STABLE_TRESH))
                    dm.backpacks[j].incConfidence(cfg.get<int>(cfg.BD_STABLE_COST));

            }


            dm.backpacks[j].incChecks();
            if(dm.backpacks[j].getChecks()>cfg.get<int>(cfg.BD_CHECKS_TRESH)) {
                if(dm.backpacks[j].getConfidence()/(double)dm.backpacks[j].getChecks() < cfg.get<double>(cfg.BD_CONFIDANCE)) {
                    dm.backpacks.erase(dm.backpacks.begin()+j);
                    

                } else {
                    dm.backpacks[j].incStableConfidance(cfg.get<int>(ConfigManager::BD_MAIN_CONFIDANCE));
                    dm.backpacks[j]._stable++;
                }
            }

            if(dm.backpacks[j]._stable > cfg.get<int>(cfg.BD_STABLE_TRESH))
            {
                dm.backpacks[j].takeSnapshot(cfg.get<int>(ConfigManager::BD_SNAPSHOT_SIZE), dm.people);
                

                cv::rectangle(tmp, dm.backpacks[j].getRoi().tl(), dm.backpacks[j].getRoi().br(), dm.backpacks[j].getColor(), 2,8,0);
                cv::rectangle(BackpackDetector::FINAL, dm.backpacks[j].getRoi().tl(), dm.backpacks[j].getRoi().br(), dm.backpacks[j].getColor(), 2,8,0);

            /*
                for(unsigned long i =0 ;i < dm.backpacks[j]._people.size(); i++){
                    cv::rectangle(tmp, dm.people[dm.backpacks[j]._people[i]]._roid.tl(), dm.people[dm.backpacks[j]._people[i]]._roid.br(), dm.backpacks[j].getColor(), 2,8,0);
                    
                }*/
               
                if(cfg.get<bool>(cfg.BD_ID_TEXT)) {
                    cv::putText(tmp,utils::str::to_string<int>(dm.backpacks[j].getID()),cv::Point(dm.backpacks[j].getRoi().x,dm.backpacks[j].getRoi().y),cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,cv::LINE_AA);
                    cv::putText(BackpackDetector::FINAL,utils::str::to_string<int>(dm.backpacks[j].getID()),cv::Point(dm.backpacks[j].getRoi().x,dm.backpacks[j].getRoi().y),cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,cv::LINE_AA);
                }
            }
        }
 if(pirintID>=0){
        for(unsigned long t = 0 ; t < DataManager::getDataManager().backpacks[BackpackDetector::pirintID]._people.size(); t++){
                cv::Rect2d roi = DataManager::getDataManager().people[DataManager::getDataManager().backpacks[BackpackDetector::pirintID]._people[t]]._roid;
                cv::rectangle(BackpackDetector::FINAL, roi.tl(), roi.br(), cv::Scalar(0,0,255), 2,8,0);

        }}

        display(ConfigManager::VIEW_FINAL_RESULT, BackpackDetector::FINAL);
        display(ConfigManager::VIEW_BD_RESULT, tmp);
    }

}


