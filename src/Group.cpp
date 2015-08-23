#include "Group.h"
Group::Group(double widthScale, double heightScale, double relativeX, double relativeY){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
}

Group::Group(double widthScale, double heightScale, double relativeX, double relativeY, Mat img){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
    _img = img;
}
Group::Group(double widthScale, double heightScale, double relativeX, double relativeY, Mat img, Mat estimation){
    _widthScale = widthScale;
    _heightScale = heightScale;
    _relativeX = relativeX;
    _relativeY = relativeY;
    _img = img;
    _estimation = estimation;
}

Group::~Group(){

}
Mat Group::getImg(){
    return _img;
}
Mat Group::getEst(){
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
