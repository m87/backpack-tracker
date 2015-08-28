#include "MedianFlowTrackingMethod.h"

MedianFlowTrackingMethod::MedianFlowTrackingMethod() {
    MEMORY("MedianFlowTrackingMethod created");
    step = 0;

}

MedianFlowTrackingMethod::~MedianFlowTrackingMethod() {
    MEMORY("MedianFlowTrackingMethod destroyed");

}

void MedianFlowTrackingMethod::init() {



}

void MedianFlowTrackingMethod::addTracker(int id, cv::Mat ref) {

    cv::Ptr<cv::Tracker> tracker = cv::TrackerMedianFlow::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void MedianFlowTrackingMethod::update(cv::Mat ref) {
    if(step++ == ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP)) {
        step=0;
        for(auto t=_trackers.begin(); t!=_trackers.end(); t++) {
            t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
        }



    }
}
