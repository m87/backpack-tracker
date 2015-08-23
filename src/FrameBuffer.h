#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include "cvcommon.h"
#include <vector>
#include "Utils.h"

class FrameBuffer
{
    int _size;
    std::vector<cv::Mat> _buffer;

    int _loop;
    bool full;

public:
    FrameBuffer (int size);
    ~FrameBuffer ();

    void setSize(int size);
    void addFrame(const cv::Mat& mat);
    
    //returns number of frames which has value at (x,y). If value=-1
    //uses treshold with tresh value
    int checkPixel(int x, int y, int value, int tresh);
    void mask(cv::Mat in, cv::Mat& input, int tresh);
    bool isFull();

};


#endif
