#include "TLDTrackingMethod.h"

TLDTrackingMethod::TLDTrackingMethod() {
    MEMORY("TLDTrackingMethod created");
    step = 0;

}

TLDTrackingMethod::~TLDTrackingMethod() {
    MEMORY("TLDTrackingMethod destroyed");

}

void TLDTrackingMethod::init() {



}

void TLDTrackingMethod::addTracker(int id, cv::Mat ref) {

    cv::Ptr<cv::Tracker> tracker = cv::TrackerTLD::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void TLDTrackingMethod::update(cv::Mat ref) {
    if(step++ == ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP)) {
        step=0;
        for(auto t=_trackers.begin(); t!=_trackers.end(); t++) {
            t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
        }



    }
}
