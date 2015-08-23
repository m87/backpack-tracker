#ifndef KNN_MD_METHOD_H
#define KNN_MD_METHOD_H
#include "MDMethod.h"
#include "Utils.h"
#include "ViewInterface.h"
#include "Managers.h"
#include "FrameBuffer.h"

class KnnMDMethod: public MDMethod, ViewInterface
{

    cv::Ptr<cv::BackgroundSubtractor> _knn;
    cv::Mat dilateElement;

public:
    KnnMDMethod ();
    ~KnnMDMethod ();
    
    void detect(const cv::Mat& input);
    void initMethod(ConfigManager& config);
    std::vector<std::vector<cv::Point> > getROIs();

};

#endif
