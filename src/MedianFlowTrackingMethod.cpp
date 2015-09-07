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

void MedianFlowTrackingMethod::removeTracker(int id) {
    std::map<int, cv::Ptr<cv::Tracker> >::iterator  it = _trackers.find(id);
    if( it != _trackers.end()) {
        _trackers.erase(it);
    }
}



void MedianFlowTrackingMethod::addTracker(int id, cv::Mat ref) {

    cv::Ptr<cv::Tracker> tracker = cv::TrackerMedianFlow::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<cv::Tracker> >(id,tracker));
}

void MedianFlowTrackingMethod::update(cv::Mat ref) {
    int limit = ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_LIMIT);
    double tresh = ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_TRESH);
    cv::Rect2d rect(limit, limit, ref.cols - 2*limit, ref.rows-2*limit);
    
    if(step++ == ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP)) {
        step=0;
        for(auto t=_trackers.begin(); t!=_trackers.end(); t++) {
            t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
            cv::Rect2d roid = DataManager::getDataManager().people[t->first]._roid ;

            cv::Rect2d res = rect &  roid;
            //remove trackier which overlaps tracking border
            if(res.width < roid.width * tresh || res.height < roid.height * tresh) {
                DataManager::getDataManager().people[t->first].trackCount = -2;
                _trackers.erase(t);
            }

        }



    }

}
