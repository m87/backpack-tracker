#ifndef Kalman_TRACKING_METHOD_H
#define Kalman_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "Utils.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Managers.h"
#include "Person.h"

class KalmanTrackingMethod : public TrackingMethod
{
    /* data */
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int kk;

public:
    KalmanTrackingMethod ();
    ~KalmanTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);

};

#endif
