#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

class Preprocessor
{
    /* data */

    VideoCapture *cap;
public:
    void getFrame(Mat &out);

    Preprocessor (string file);
    virtual ~Preprocessor ();

};


#endif
