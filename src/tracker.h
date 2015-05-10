#ifndef TRACKER_H
#define TRACKER_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

class Tracker
{
    /* data */

public:
    Tracker ();
    virtual ~Tracker ();

    vector< Rect > track();
    
    void print(vector<Rect> rects, Mat &input);


};

#endif
