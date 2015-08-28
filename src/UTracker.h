#ifndef UTRACKER_H
#define UTRACKER_H

#include "cvcommon.h"
#include <vector>
#include <opencv2/tracking/tracker.hpp>
#include <map>
#include "TrackingMethod.h"
#include "MILTrackingMethod.h"
#include "KalmanTrackingMethod.h"
#include "BoostingTrackingMethod.h"
#include "MedianFlowTrackingMethod.h"
#include "TLDTrackingMethod.h"
#include "ViewInterface.h"

class UTracker : public ViewInterface
{
    std::unique_ptr<TrackingMethod> _method;

public:
    UTracker (std::string method);
    ~UTracker ();
    void addTracker(int id, cv::Mat ref);
    void update(cv::Mat ref);
    void init();

};

#endif
