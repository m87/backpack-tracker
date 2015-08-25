#include "Backpack.h"
long Backpack::ID = 0;

Backpack::Backpack(cv::Rect roi, cv::Mat img, cv::Mat base){
   // MEMORY("Backpack created"); 
    _id = ID++;
    _roi=roi;
    img.copyTo(_img);
    base.copyTo(_base);
    _confidence = 0;
    _checks = 0;
    _stable = 0;
    isbase = true;
}


Backpack::~Backpack(){
    //MEMORY("Backpack destroyed");

}

void Backpack::setNewBase(cv::Mat base){
    if(isbase){
        base.copyTo(_base);
        base = false;
    }
}


void Backpack::incConfidence(int i){
    _confidence+=i;
}

int Backpack::getConfidence(){
    return _confidence;
}

cv::Mat Backpack::getImg(){
    return _img;
}

cv::Mat Backpack::getBase(){
    return _base;
}

long Backpack::getID(){
    return _id;
}

cv::Rect Backpack::getRoi(){
    return _roi;
}

void Backpack::incChecks(int i){
    _checks+=i;
}

int Backpack::getChecks(){
    return _checks;
}


void Backpack::shrink(cv::Mat sum){
    try{
        cv::Mat tmp = sum(_roi);
        std::vector<cv::Vec4i> hierarchy;
std::vector<std::vector<cv::Point> > contours;
        findContours(tmp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)  );
        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<std::vector<cv::Point> > contoursPoly(contours.size());

            approxPolyDP(cv::Mat(contours[0]),contoursPoly[0],10,false);
            boundRect[0] = boundingRect(cv::Mat(contoursPoly[0]));
            
            _roi = boundRect[0];

}catch(cv::Exception e){}
}
