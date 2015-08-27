#include "BoostingTrackingMethod.h"

BoostingTrackingMethod::BoostingTrackingMethod(){
MEMORY("BoostingTrackingMethod created");
kk = 0;    

}

BoostingTrackingMethod::~BoostingTrackingMethod(){
MEMORY("BoostingTrackingMethod destroyed");

}

void BoostingTrackingMethod::init(){



}

void BoostingTrackingMethod::addTracker(int id, cv::Mat ref){
    
    cv::Ptr<cv::Tracker> tracker = cv::TrackerBoosting::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void BoostingTrackingMethod::update(cv::Mat ref){
    if(kk++ == 5){
    kk=0;
    for(auto t=_trackers.begin(); t!=_trackers.end();t++){
        t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
    }
 


}}
