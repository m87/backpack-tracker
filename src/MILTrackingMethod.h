#ifndef MIL_TRACKING_METHOD_H
#define MIL_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "Utils.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Managers.h"
#include "Person.h"

class MILTrackingMethod : public TrackingMethod
{
    /* data */
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int kk;

public:
    MILTrackingMethod ();
    ~MILTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);

};

#endif
