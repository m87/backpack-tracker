#ifndef BACKPACK_DETECTOR_H
#define BACKPACK_DETECTOR_H
#include "cvcommon.h"
#include "Utils.h"
#include "Managers.h"
#include "ViewInterface.h"

class BackpackDetector : public ViewInterface
{
    const static std::string BG_MOG_METHOD, BG_KNN_METHOD;

    cv::Ptr<cv::BackgroundSubtractor> _mog2;
    cv::Ptr<cv::BackgroundSubtractor> _bgLong;
    cv::Mat bg;

public:
    BackpackDetector ();
    ~BackpackDetector ();

    void detect(cv::Mat ref);
    void update(cv::Mat ref);
    void bgDiffMethod(cv::Mat ref);


};
#endif
