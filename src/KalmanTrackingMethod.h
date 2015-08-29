#ifndef Kalman_TRACKING_METHOD_H
#define Kalman_TRACKING_METHOD_H

#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"
#include "TrackingMethod.h"

class KalmanTrackingMethod : public TrackingMethod
{
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;

public:
    KalmanTrackingMethod ();
    ~KalmanTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);
    void removeTracker(int id);

};

#endif
