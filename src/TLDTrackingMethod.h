#ifndef TLD_TRACKING_METHOD_H
#define TLD_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "opencv2/tracking/tracker.hpp"
#include <map>
#include "Person.h"
#include "TimeManager.h"
#include "PeopleDetector.h"


/** Class for tld tracking method.
 * @see TrackingMethod
 */
class TLDTrackingMethod : public TrackingMethod
{
    std::map<int, cv::Ptr<cv::Tracker> > _trackers;
    int step;
    std::map<int, long > _life;

public:
    TLDTrackingMethod ();
    ~TLDTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);
    void removeTracker(int id);

};

#endif
