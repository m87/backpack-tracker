#ifndef MEDIANFLOW_TRACKING_METHOD_H
#define MEDIANFLOW_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"

/** Class for Median Flow tracking method
 * @see TrackingMethod
 */
class MedianFlowTrackingMethod : public TrackingMethod
{
    // list of trackers
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int step;

public:
    MedianFlowTrackingMethod ();
    ~MedianFlowTrackingMethod ();
    //update trackers
    void update(cv::Mat ref);
    //initialization
    void init();
    //add new tracker
    void addTracker(int id, cv::Mat ref);
    //remove tracker
    void removeTracker(int id);

};

#endif
