#ifndef BACKPACK_DETECTOR_H
#define BACKPACK_DETECTOR_H
#include "cvcommon.h"
#include "ViewInterface.h"
#include <opencv2/highgui/highgui.hpp>

class BackpackDetector : public ViewInterface
{
    const static std::string BG_MOG_METHOD, BG_KNN_METHOD;

    cv::Ptr<cv::BackgroundSubtractor> _mog2;
    cv::Ptr<cv::BackgroundSubtractor> _bgLong;
    cv::Mat bg;
    
public:
    BackpackDetector ();
    ~BackpackDetector ();
    static cv::Mat FINAL, FINAL_CP;
    static int pirintID;


    void detect(cv::Mat ref);
    void update(cv::Mat ref);
    void bgDiffMethod(cv::Mat ref);
    static void callbackMouse(int event, int x ,int y , int flags, void* userdata);


};
#endif
