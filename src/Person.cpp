#include "Person.h"

long Person::ID = 1;

Person::Person(Rect roi){
    _roi = roi;
    _id = Person::ID;
    Person::ID++;
}

Person::~Person(){

}
Rect Person::getROI(){
    return _roi;
}

long Person::getID(){
    return _id;
}

void Person::setCorners(vector<Point2f> corners){
    _corners.clear();
    for(unsigned long i=0; i< corners.size();i++)
        _corners.push_back(corners[i]); 
}

vector<Point2f> Person::getCorners(){
    return _corners;
}

void Person::reviewCorners(){

}

void Person::updateROI(){
    
}

void Person::setCornersPrev(vector<Point2f> corners){
    _corners_prev.clear();
    for(unsigned long i=0; i< corners.size();i++)
        _corners_prev.push_back(corners[i]); 
}
void Person::setShift(int x, int y){
    _roi.x +=x;
    _roi.y +=y;
}
vector<Point2f> Person::getCornersPrev(){
    return _corners_prev;
}
