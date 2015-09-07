#ifndef PERSON_H
#define PERSON_H
#include "cvcommon.h"
#include <vector>
#include <cmath>

/**
 * Person representation
 * @see PeopleDetector
 * @see BackpackDetector
 * @see DataManager
 * @see UTracker
 */
class Person
{
    long _id;
    static long ID;
    //initial roi 
    cv::Rect _roi;
    cv::Mat _img;

public:
    /// image for security
    int trackCount;
    ///roi for tracking
    cv::Rect2d _roid;
    long getID();
    cv::Rect getROI();
    Person (cv::Rect roi);
    Person(){};
    ~Person ();

};

#endif
