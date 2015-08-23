#ifndef BACKPACK_DETECTOR_H
#define BACKPACK_DETECTOR_H
#include "cvcommon.h"
#include "Utils.h"

class BackpackDetector
{

public:
    BackpackDetector ();
    ~BackpackDetector ();

    void detect(cv::Mat ref);

};
#endif
