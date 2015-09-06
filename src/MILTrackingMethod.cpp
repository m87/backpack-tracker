#include "MILTrackingMethod.h"

MILTrackingMethod::MILTrackingMethod() {
    MEMORY("MILTrackingMethod created");
    step = 0;

}

MILTrackingMethod::~MILTrackingMethod() {
    MEMORY("MILTrackingMethod destroyed");

}

void MILTrackingMethod::init() {



}
void MILTrackingMethod::removeTracker(int id){
    std::map<int, cv::Ptr<cv::Tracker> >::iterator  it = _trackers.find(id);
    if( it != _trackers.end()){
    }
}
void MILTrackingMethod::addTracker(int id, cv::Mat ref) {
    cv::Ptr<cv::Tracker> tracker = cv::TrackerMIL::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void MILTrackingMethod::update(cv::Mat ref) {
    int limit = ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_LIMIT);
    double tresh = ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_TRESH);
    cv::Rect2d rect(limit, limit, ref.cols - 2*limit, ref.rows-2*limit);

    if(step++ == ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP)) {
        step=0;
        for(auto t=_trackers.begin(); t!=_trackers.end(); t++) {
            t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
            cv::Rect2d roid = DataManager::getDataManager().people[t->first]._roid ;

            cv::Rect2d res = rect &  roid;
            if(res.width < roid.width * tresh || res.height < roid.height * tresh){
            DataManager::getDataManager().people[t->first].trackCount = -2;
        _trackers.erase(t);
            }

        }



    }
}
