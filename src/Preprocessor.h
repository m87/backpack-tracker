#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string>
#include <vector>
#include "GenericException.h"
#include <map>
#include "cvcommon.h"
#include "ViewInterface.h"

/** Performes initial processing. Manages frame buffer */
class Preprocessor : public ViewInterface
{

    std::unique_ptr<cv::VideoCapture> _cap;
    std::vector<cv::Mat> _frameBuffer;
    unsigned long _frameBufferSize;
    unsigned long _currentFrameBufferPos;
    std::map<std::string, cv::Mat&> windows;

public:
    void getFrame(cv::Mat &out, cv::Mat &out_real,float w=-1.0f, float h=-1.0f, bool gray=false);
    void getFrame(cv::Mat &out,float w=-1.0f, float h=-1.0f, bool gray=false);
    void skipNFrames(unsigned long n);
    void saveFrame(cv::Mat frame);
    void clearFrameBuffer();
    cv::Mat getFrameFromBuffer(unsigned long n);
    unsigned long getFrameBufferSize();
    unsigned long getCurrentFrameBufferSize();

    cv::Mat getStructuringElement(int size, int type = 0);

    Preprocessor (std::string file);
    Preprocessor (std::string file, unsigned long n);
    virtual ~Preprocessor ();
    void printParams(cv::Algorithm a);



};


#endif
