#include "BackpackDetector.h"

BackpackDetector::BackpackDetector(){
    MEMORY("BackpackDetector created");
    _mog2 = cv::createBackgroundSubtractorMOG2(
               25,400,false
                );
 

}

BackpackDetector::~BackpackDetector(){
    MEMORY("BackpackDetector destroyed");
}


void BackpackDetector::detect(cv::Mat ref){
    bgDiffMethod(ref);   

}

bool checkDiff(cv::Mat diff){
int count_white = 0;
for( int y = 0; y < diff.rows; y++  ) {
    for( int x = 0; x < diff.cols; x++  ) {
            if ( diff.at<uchar>(y,x) == 255  ) {
                        count_white++;
                              
            } 
                

    }
}
if(count_white / (double)(diff.cols*diff.rows) > 0.5 )
{
    return true;
}

    return false;
}

bool checkOverlapping(cv::Rect A, cv::Rect B){
    cv::Rect inter = A & B;
    if(inter.width > A.width * 0.95  || inter.height > A.height *0.95)
    {   
        return true;

    }
    return false;

}

bool checkOverlapping2(cv::Rect A, cv::Rect B){
    cv::Rect inter = A & B;
    if(inter.width > B.width * 0.95  || inter.height > B.height *0.95)
    {   
        return true;

    }
    return false;

}
void BackpackDetector::bgDiffMethod(cv::Mat ref){
    DataManager dm = DataManager::getDataManager();
    std::vector<Group> groups = dm.getGroups();

    cv::Mat estF, estBg;

    _mog2->apply(ref,estF);
    _mog2->getBackgroundImage(estBg);
        cv::Mat out;

      DataManager::getDataManager().addFrame(estBg);


      if(DataManager::getDataManager().isFull()){
            cv::Mat sum; 
            cv::absdiff(DataManager::getDataManager().get(0),dm.cBG,out);
            cv::threshold(out,out,35,255,0);

           cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*2 + 1, 2*2+1  ), cv::Point( 2, 2  )  );
           cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*8 + 1, 2*8+1  ), cv::Point( 8, 8  )  );
           cv::erode(out,out,erodeElement);
           cv::dilate(out,out,dilateElement);

            out.copyTo(sum);

          for(int i =1; i< DataManager::getDataManager().getSize();i++){
            cv::absdiff(DataManager::getDataManager().get(i),dm.cBG,out);
            cv::threshold(out,out,25,255,0);

           cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*3 + 1, 2*3+1  ), cv::Point( 3, 3  )  );
           cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*8 + 1, 2*8+1  ), cv::Point( 8, 8  )  );
           cv::erode(out,out,erodeElement);
           cv::dilate(out,out,dilateElement);
           cv::bitwise_and(sum,out,sum);

          }

     // imshow("asd",dm.cBG);
     // imshow("asd1",sum);

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

          for(unsigned long j =0; j< DataManager::getDataManager().backpacks.size();j++){
              if(checkOverlapping(DataManager::getDataManager().backpacks[j].getRoi(), boundRect[i])){
          //        int confidence = DataManager::getDataManager().backpacks[j].getConfidence();
           //       int cecks = DataManager::getDataManager().backpacks[j].getChecks();
            //      int stable = DataManager::getDataManager().backpacks[j]._stable;
             //     DataManager::getDataManager().backpacks.erase(DataManager::getDataManager().backpacks.begin()+j);
              //    Backpack backpack(boundRect[i], dm.cBG(boundRect[i]),dm.cBG(boundRect[i]));
             //     backpack.incChecks(cecks);
             //     backpack.incConfidence(confidence);
              //    backpack._stable = stable;
                //    DataManager::getDataManager().backpacks.push_back(backpack);
                    ok=false;
                    break;
              }
            if(checkOverlapping2(DataManager::getDataManager().backpacks[j].getRoi(), boundRect[i])){
                ok=false;
                    break;
              }


          }

          if(ok){
                   Backpack backpack(boundRect[i], dm.cBG(boundRect[i]),dm.cBG(boundRect[i]));
                    DataManager::getDataManager().backpacks.push_back(backpack);
              
          }

            //rectangle(tmp, DataManager::getDataManager().backpacks[i].getRoi().tl(), DataManager::getDataManager().backpacks[i].getRoi().br(), cv::Scalar(0,255,0), 2,8,0);
                 }

          for(unsigned long j =0; j< DataManager::getDataManager().backpacks.size();j++){
            
              cv::Mat sum; 

            cv::absdiff(DataManager::getDataManager().get(0)(DataManager::getDataManager().backpacks[j].getRoi()),DataManager::getDataManager().backpacks[j].getBase(),out);
            cv::threshold(out,out,35,255,0);

           cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*2 + 1, 2*2+1  ), cv::Point( 2, 2  )  );
           cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*8 + 1, 2*8+1  ), cv::Point( 8, 8  )  );
           cv::erode(out,out,erodeElement);
           cv::dilate(out,out,dilateElement);

            out.copyTo(sum);

          for(int i =1; i< DataManager::getDataManager().getSize();i++){
            cv::absdiff(DataManager::getDataManager().get(i)(DataManager::getDataManager().backpacks[j].getRoi()),DataManager::getDataManager().backpacks[j].getBase(),out);
            cv::threshold(out,out,35,255,0);

           cv::Mat erodeElement = cv::getStructuringElement( 0, cv::Size( 2*2 + 1, 2*2+1  ), cv::Point( 2, 2  )  );
           cv::Mat dilateElement = cv::getStructuringElement( 0, cv::Size( 2*8 + 1, 2*8+1  ), cv::Point( 8, 8  )  );
           cv::erode(out,out,erodeElement);
           cv::dilate(out,out,dilateElement);
           cv::bitwise_and(sum,out,sum);

          }

//DataManager::getDataManager().backpacks[j].shrink(sum);

          if(checkDiff(sum))
DataManager::getDataManager().backpacks[j].incConfidence();

DataManager::getDataManager().backpacks[j].incChecks();
if(DataManager::getDataManager().backpacks[j].getChecks()>10){
if(DataManager::getDataManager().backpacks[j].getConfidence()/(double)DataManager::getDataManager().backpacks[j].getChecks() < 0.5){
   DataManager::getDataManager().backpacks.erase(DataManager::getDataManager().backpacks.begin()+j);

}else{
    
  DataManager::getDataManager().backpacks[j]._stable++;
}
}

if(DataManager::getDataManager().backpacks[j]._stable > 100)
rectangle(tmp, DataManager::getDataManager().backpacks[j].getRoi().tl(), DataManager::getDataManager().backpacks[j].getRoi().br(), cv::Scalar(0,255,0), 2,8,0);

          }

      imshow("asd1",tmp);
       }

}
