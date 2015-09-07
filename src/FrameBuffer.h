#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <memory>
#include "Utils.h"

/** Framebuffer class
 * @see DataManager
 */
class FrameBuffer
{
    int _size;
    std::vector<cv::Mat> _buffer;
    //current buffer position
    int _loop;
    bool _full;

public:
    FrameBuffer (int size);
    FrameBuffer ();
    ~FrameBuffer ();

    void setSize(int size);
    void addFrame(const cv::Mat& mat);
    cv::Mat get(int i);
    //get the oldest frame in buffer
    cv::Mat getLast();
    //get the youngest frame in buffer
    cv::Mat getFirst();
    int getSize(){return _size;}
    bool isFull();

};


#endif
