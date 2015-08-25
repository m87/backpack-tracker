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
    bool _full;
    int _last;
    int _first;

public:
    FrameBuffer (int size);
    FrameBuffer ();
    ~FrameBuffer ();

    void setSize(int size);
    void addFrame(const cv::Mat& mat);
    cv::Mat get(int i);
    cv::Mat getLast();
    cv::Mat getFirst();
    int getSize(){return _size;}
    
    //returns number of frames which has value at (x,y). If value=-1
    //uses treshold with tresh value
    int checkPixel(int x, int y, int value, int tresh);
    void mask(cv::Mat in, cv::Mat& input, int tresh);
    bool isFull();

};


#endif
