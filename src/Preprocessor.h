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

public:
    bool getFrame(cv::Mat &out, cv::Mat &out_real,float w=-1.0f, float h=-1.0f, bool gray=false);
    bool getFrame(cv::Mat &out,float w=-1.0f, float h=-1.0f, bool gray=false);
    Preprocessor (std::string file);
    virtual ~Preprocessor ();



};


#endif
