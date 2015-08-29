#include "BoostingTrackingMethod.h"

BoostingTrackingMethod::BoostingTrackingMethod() {
    MEMORY("BoostingTrackingMethod created");
    step = 0;

}

BoostingTrackingMethod::~BoostingTrackingMethod() {
    MEMORY("BoostingTrackingMethod destroyed");

}

void BoostingTrackingMethod::init() {



}

void BoostingTrackingMethod::removeTracker(int id){

    std::map<int, cv::Ptr<cv::Tracker> >::iterator  it = _trackers.find(id);
    if( it != _trackers.end()){
        _trackers.erase(it);
    }
}



void BoostingTrackingMethod::addTracker(int id, cv::Mat ref) {

    cv::Ptr<cv::Tracker> tracker = cv::TrackerBoosting::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void BoostingTrackingMethod::update(cv::Mat ref) {
    if(step++ == ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP)) {
        step=0;
        for(auto t=_trackers.begin(); t!=_trackers.end(); t++) {
            t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
        }
    }
}
