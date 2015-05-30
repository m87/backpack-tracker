#ifndef PERSON_H
#define PERSON_H
#include <opencv2/opencv.hpp>

using namespace cv;

class Person
{
    /* data */
    long _id;
    static long ID;
    Rect _roi;

public:
    long getID();
    Person (Rect roi);
    ~Person ();

};

#endif
