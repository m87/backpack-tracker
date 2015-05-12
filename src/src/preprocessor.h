#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "GenericException.h"

using namespace std;
using namespace cv;

class Preprocessor
{
    /* data */

    VideoCapture *_cap;
    vector<Mat> _frameBuffer;
    unsigned long _frameBufferSize;
    unsigned long _currentFrameBufferPos;

public:
    void getFrame(Mat &out, Mat &out_real,float w=-1.0f, float h=-1.0f, bool gray=false);
    void getFrame(Mat &out,float w=-1.0f, float h=-1.0f, bool gray=false);
    void skipNFrames(unsigned long n);
    void saveFrame(Mat frame);
    void clearFrameBuffer();
    Mat getFrameFromBuffer(unsigned long n);
    unsigned long getFrameBufferSize();
    unsigned long getCurrentFrameBufferSize();

    void getAvgFrame(Mat &output);

    Mat getStructuringElement(int size, int type = 0);

    Preprocessor (string file);
    Preprocessor (string file, unsigned long n);
    virtual ~Preprocessor ();

};


#endif
