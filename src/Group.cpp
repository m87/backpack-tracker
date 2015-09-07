#include "Group.h"
Group::Group(double widthScale, double heightScale, double relativeX, double relativeY){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
}

Group::Group(double widthScale, double heightScale, double relativeX, double relativeY, cv::Mat img){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
    _img = img;
}
Group::Group(double widthScale, double heightScale, double relativeX, double relativeY, cv::Mat img, cv::Mat estimation, cv::Rect roi){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
    _img = img;
    _estimation = estimation;
    _roi = roi;
}

Group::~Group(){

}

cv::Rect Group::getRoi(){
    return _roi;
}

cv::Mat Group::getImg(){
    return _img;
}
cv::Mat Group::getEst(){
    return _estimation;
}
double Group::getWidthScale(){
    return _widthScale;
}

double Group::getHeightScale(){
    return _heightScale;
}

double Group::getRelativeX(){
    return _relativeX;
}

double Group::getRelativeY(){
    return _relativeY;
}
