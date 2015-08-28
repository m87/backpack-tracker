#include "Person.h"
#include <iostream>
#include <cmath>

long Person::ID = 1;

Person::Person(Rect roi) {
    movBuffSize=0;
    _roi = roi;
    _roid = Rect2d(roi);
    _id = Person::ID;
    Person::ID++;
    accX=0.0;
    accX2=0.0;
    accY=0.0;
    accY2=0.0;
}

Person::~Person() {

}
Rect Person::getROI() {
    return _roi;
}

long Person::getID() {
    return _id;
}

void Person::setCorners(vector<Point2f> corners) {
    _corners.clear();
    for(unsigned long i=0; i< corners.size(); i++)
        _corners.push_back(corners[i]);
}

vector<Point2f> Person::getCorners() {
    return _corners;
}
bool Person::isInside(Point2f point) {
    if(point.x > _roi.x + _roi.width || point.x < _roi.x
            || point.y > _roi.y + _roi.height || point.y <_roi.y)
        return false;

    return true;
}

void Person::reviewCorners() {
    for(unsigned long i =0; i<_corners.size() ; i++) {
        if(!_roi.contains(_corners[i])) {
            _corners.erase(_corners.begin()+i);
            _corners_prev.erase(_corners_prev.begin()+i);
        }
    }
}

bool Person::isOutside(Mat m) {

    return !(0 <= _roi.x && 0 <= _roi.width && _roi.x + _roi.width <= m.cols && 0 <= _roi.y && 0 <= _roi.height && _roi.y + _roi.height <= m.rows);



}

bool Person::isMoveing() {
    if(movBuff.size()==10) {
        for(unsigned long i=0; i<movBuff.size(); i++) {
            if(movBuff[i]==true)
                return true;
        }
        return false;

    }
    return true;
}

void Person::updateROI(vector<uchar> _status) {

    for(unsigned long i=0; i< _corners.size() ; i++) {
        if(_status[i] != 1 ) {
            _corners.erase(_corners.begin()+i);
            _corners_prev.erase(_corners_prev.begin()+i);
        }
    }
    double avgX =0.0;
    double avgX2 =0.0;
    double avgY = 0.0;
    double avgY2 = 0.0;
    for(unsigned long i=0; i< _corners.size() ; i++) {
        avgX+=_corners[i].x;
        avgX2+=_corners_prev[i].x;
        avgY+=_corners[i].y;
        avgY2+=_corners_prev[i].y;
    }
    avgX/=_corners.size();
    avgX2/=_corners.size();
    avgY/=_corners.size();
    avgY2/=_corners.size();


    Point2f a(avgX,avgY);
    Point2f b(avgX2,avgY2);
    accX += a.x-b.x;
    accY += a.y-b.y;

    Rect roi = _roi;
    Point c(accX,accY);
    accX -= (int)accX;
    accY -= (int)accY;

    _roi +=c;
    error(!(_roi.x==roi.x && _roi.y==roi.y)) ;

    reviewCorners();

}

void Person::error(bool er) {
    if(movBuff.size()<10) {
        movBuff.push_back(er);
    } else {
        movBuff[movBuffSize++] = er;
        if(movBuffSize == movBuff.size()) {
            movBuffSize=0;
        }
    }

}

bool Person::ROIOverlapping(Rect2d riod2) {
    Rect2d RectA = _roid;
    Rect2d RectB = riod2;
    return (RectA.x < RectB.x+RectB.width && RectA.x+RectA.width > RectB.x && RectA.y < RectB.y+ RectB.height && RectA.y+RectA.height > RectB.y)  ;
}

void Person::setCornersPrev(vector<Point2f> corners) {
    _corners_prev.clear();
    for(unsigned long i=0; i< corners.size(); i++)
        _corners_prev.push_back(corners[i]);
}
void Person::setShift(int x, int y) {
}
vector<Point2f> Person::getCornersPrev() {
    return _corners_prev;
}
