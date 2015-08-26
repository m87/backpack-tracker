#ifndef TRACKER_H
#define TRACKER_H

#include "cvcommon.h"
#include <vector>
#include <opencv2/tracking/tracker.hpp>
#include <map>
#include "Utils.h"
#include "TrackingMethod.h"
#include "MILTrackingMethod.h"

class Tracker
{
    std::unique_ptr<TrackingMethod> _method;

public:
    Tracker (std::string method);
    ~Tracker ();
    void addTracker(int id, cv::Mat ref);
    void update(cv::Mat ref);
    void init();

};

#endif
