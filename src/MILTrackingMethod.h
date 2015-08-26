#ifndef MIL_TRACKING_METHOD_H
#define MIL_TRACKING_METHOD_H

#include "TrackingMethod.h"
#include "cvcommon.h"
#include "Utils.h"

class MILTrackingMethod : public TrackingMethod
{
    /* data */

public:
    MILTrackingMethod ();
    ~MILTrackingMethod ();

    void update(cv::Mat ref);
    void init();
    void addTracker(int id, cv::Mat ref);

};

#endif
