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
