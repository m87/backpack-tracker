#ifndef TRACKER_H
#define TRACKER_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Person.h"

using namespace std;
using namespace cv;

class Tracker
{
    /* data */
    vector<Person> people;

public:
    Tracker ();
    ~Tracker ();
    bool isTracked(Person person);

    vector< Rect > track(Person person, Mat ref);
    
    void print(vector<Rect> rects, Mat &input);


};

#endif
