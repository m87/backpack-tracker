#ifndef TRACKING_METHOD_H
#define TRACKING_METHOD_H

#include "cvcommon.h"
#include "DataManager.h"
#include "ConfigManager.h"

/** Abstract tracking method class
 * @see MILTrackingMethod
 * @see TLDTrackingMethod
 * @see MedianFlowTrackingMethod
 * @see BoostingTrackingMethod
 */
class TrackingMethod
{
public:
    /**add new tracker
     * @param id id of person 
     */
    virtual void addTracker(int id, cv::Mat ref)=0;
    /**remove tracker
     * @parar id id of person
     */
    virtual void removeTracker(int id)=0;
    //initialization
    virtual void init()=0;
    //update trackers
    virtual void update(cv::Mat ref)=0;

};


#endif
