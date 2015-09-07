#include "Person.h"

long Person::ID = 1;

Person::Person(cv::Rect roi) {
    _roi = roi;
    _roid = cv::Rect2d(roi);
    _id = Person::ID;
    Person::ID++;
    trackCount = 0;
}

Person::~Person() {

}
cv::Rect Person::getROI() {
    return _roi;
}

long Person::getID() {
    return _id;
}

