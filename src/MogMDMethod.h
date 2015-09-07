#ifndef MOG_MD_METHOD_H
#define MOG_MD_METHOD_H
#include "MDMethod.h"
#include "Utils.h"
#include "ViewInterface.h"
#include "ConfigManager.h"
#include "TimeManager.h"
#include "DataManager.h"
#include "FrameBuffer.h"

/** Class for mog movement detection method
 */
class MogMDMethod: public MDMethod, ViewInterface
{

    cv::Ptr<cv::BackgroundSubtractor> _mog2;
    cv::Mat dilateElement, erodeElement;

public:
    MogMDMethod ();
    ~MogMDMethod ();
    
    void detect(const cv::Mat& input);
    void initMethod(ConfigManager& config);
    std::vector<std::vector<cv::Point> > getROIs();

};

#endif
