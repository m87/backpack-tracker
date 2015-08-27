#ifndef TLD_TRACKING_METHOD_H
#define TLD_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "Utils.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Managers.h"
#include "Person.h"

class TLDTrackingMethod : public TrackingMethod
{
    /* data */
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int kk;

public:
    TLDTrackingMethod ();
    ~TLDTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);

};

#endif
