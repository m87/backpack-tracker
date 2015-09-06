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
void TLDTrackingMethod::removeTracker(int id){
    std::map<int, cv::Ptr<cv::Tracker> >::iterator  it = _trackers.find(id);
    if( it != _trackers.end()){
        _trackers.erase(it);
    }
}

void TLDTrackingMethod::addTracker(int id, cv::Mat ref) {

    cv::Ptr<cv::Tracker> tracker = cv::TrackerTLD::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void TLDTrackingMethod::update(cv::Mat ref) {
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



    }}
