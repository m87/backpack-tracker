#ifndef MOVEMENT_DETECTOR_H
#define MOVEMENT_DETECTOR_H
#include "Utils.h"
#include "MDMethod.h"
#include "MogMDMethod.h"
#include "KnnMDMethod.h"
#include "cvcommon.h"
#include "ViewInterface.h"
#include <vector>
#include "Group.h"

class MovementDetector : public ViewInterface
{
    std::string _type;
    std::unique_ptr<MDMethod> mdMethod;


    const static std::string MOG_METHOD, KNN_METHOD;

public:
    MovementDetector (std::string type);
    ~MovementDetector ();

    void detect(const cv::Mat& input);


};

#endif
