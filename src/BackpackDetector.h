#ifndef BACKPACK_DETECTOR_H
#define BACKPACK_DETECTOR_H
#include "cvcommon.h"
#include "Utils.h"
#include "Managers.h"

class BackpackDetector
{

    cv::Ptr<cv::BackgroundSubtractor> _mog2;
    cv::Mat bg;

public:
    BackpackDetector ();
    ~BackpackDetector ();

    void detect(cv::Mat ref);
    void bgDiffMethod(cv::Mat ref);


};
#endif
