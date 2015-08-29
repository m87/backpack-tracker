#ifndef MEDIANFLOW_TRACKING_METHOD_H
#define MEDIANFLOW_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"

class MedianFlowTrackingMethod : public TrackingMethod
{
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int step;

public:
    MedianFlowTrackingMethod ();
    ~MedianFlowTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);
    void removeTracker(int id);

};

#endif
