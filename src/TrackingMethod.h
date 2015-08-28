#ifndef TRACKING_METHOD_H
#define TRACKING_METHOD_H

#include "cvcommon.h"


class TrackingMethod
{
public:
    virtual void addTracker(int id, cv::Mat ref)=0;
    virtual void init()=0;
    virtual void update(cv::Mat ref)=0;

};


#endif
