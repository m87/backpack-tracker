#ifndef MIL_TRACKING_METHOD_H
#define MIL_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"
#include "TimeManager.h"
#include "PeopleDetector.h"

/** Class for mil tracking method
 * @see TrackingMethod
 * */
class MILTrackingMethod : public TrackingMethod
{
    //list of tracker
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    std::map<int, long > _life;
    int step;
    

public:
    MILTrackingMethod ();
    ~MILTrackingMethod ();
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
