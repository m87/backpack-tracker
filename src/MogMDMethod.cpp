#include "MogMDMethod.h"

MogMDMethod::MogMDMethod() {
    MEMORY("MogMDMethod created");

}

MogMDMethod::~MogMDMethod() {
    MEMORY("MogMDMethod destroyed");
}


void MogMDMethod::detect(const cv::Mat& input) {
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat estForeground,      //mog2 result
       estBackground,          //mog2 result
       contoursMat,            //tmp required to show all steps
       dilated,                //after dilatation
       tmp,tmpF;
    input.copyTo(tmp);

    _mog2->apply(input, estForeground);
    _mog2->getBackgroundImage(estBackground);


    display(ConfigManager::VIEW_MOG_BACKGROUND, estBackground);
    display(ConfigManager::VIEW_MOG_FOREGROUND, estForeground);



    dilate(estForeground,dilated, dilateElement);
    display(ConfigManager::VIEW_MOG_DILATATION, dilated);

    dilated.copyTo(contoursMat);
    dilated.copyTo(tmpF);


    std::vector<std::vector<cv::Point> > contours;
    if(TimeManager::getTimeManager().time() % ConfigManager::getConfigManager().get<int>(ConfigManager::MD_DETECTION_STEP) == 0) {
        findContours( contoursMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)  );

        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<std::vector<cv::Point> > contoursPoly(contours.size());

        for( unsigned long i = 0; i< contours.size(); i++  )
        {
            cv::approxPolyDP(cv::Mat(contours[i]),contoursPoly[i],10,false);
            boundRect[i] = boundingRect(cv::Mat(contoursPoly[i]));

            cv::rectangle(tmp, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 2,8,0);
            std::vector<cv::Rect> found, found_filtered;
            cv::Mat img1 = tmp(boundRect[i]);
            cv::Mat imgF = tmpF(boundRect[i]);
            cv::Mat img, imgFF;
            cv::resize(img1,img,cv::Size((img1.cols/(double)img1.rows)*ConfigManager::getConfigManager().get<int>(ConfigManager::MD_GROUP_SIZE_FIX),ConfigManager::getConfigManager().get<int>(ConfigManager::MD_GROUP_SIZE_FIX)));
            cv::resize(imgF,imgFF,cv::Size((imgF.cols/(double)imgF.rows)*ConfigManager::getConfigManager().get<int>(ConfigManager::MD_GROUP_SIZE_FIX),ConfigManager::getConfigManager().get<int>(ConfigManager::MD_GROUP_SIZE_FIX)));

            if(!(boundRect[i].width > ConfigManager::getConfigManager().get<double>(ConfigManager::MD_GROUP_WINDOW_TRESH) * input.rows || boundRect[i].width > ConfigManager::getConfigManager().get<double>(ConfigManager::MD_GROUP_WINDOW_TRESH) * input.rows)) {
                Group group(img1.cols/(double)img.cols, img1.rows/(double)img.rows,boundRect[i].x, boundRect[i].y,img, imgFF, boundRect[i]);
                DataManager::getDataManager().addGroup(group);

            }
        }
    }
    display(ConfigManager::VIEW_MOG_RESULT, tmp);



}



void MogMDMethod::initMethod(ConfigManager& config) {
    _mog2 = cv::createBackgroundSubtractorMOG2(
                config.get<int>(ConfigManager::MD_MOG_HISTORY),
                config.get<int>(ConfigManager::MD_MOG_MIXTURES),
                config.get<bool>(ConfigManager::MD_MOG_SHADOW)
            );

    int tmpSize = ConfigManager::getConfigManager().get<int>(ConfigManager::MD_MOG_DILATATION);
    dilateElement = cv::getStructuringElement( 0, cv::Size( 2*tmpSize + 1, 2*tmpSize+1  ), cv::Point( tmpSize, tmpSize  )  );


}


std::vector<std::vector<cv::Point> > MogMDMethod::getROIs() {

    std::vector<std::vector<cv::Point> > c;
    return c;
}
