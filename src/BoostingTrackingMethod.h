#ifndef Boosting_TRACKING_METHOD_H
#define Boosting_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"


/** Class for boosting tracking method
 * @see TrackingMethod
 * */
class BoostingTrackingMethod : public TrackingMethod
{
    ///trackers list
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int step;

public:
    BoostingTrackingMethod ();
    ~BoostingTrackingMethod ();
    ///update trackers
    void update(cv::Mat ref);
    ///initialization
    void init();
    ///add new tracker
    void addTracker(int id, cv::Mat ref);
    ///remove tracker
    void removeTracker(int id);

};

#endif
