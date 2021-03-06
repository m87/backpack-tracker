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
if(TimeManager::getTimeManager().time() > ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_AVG_START)){
                if(DataManager::getDataManager().people[id]._roid.height < ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_AVG_TRASH) * DataManager::getDataManager().avgH || DataManager::getDataManager().people[id]._roid.width < ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_AVG_TRASH) * DataManager::getDataManager().avgW) {
            DataManager::getDataManager().people[id].trackCount = _TRACKER_REMOVED;
            return; 
                }
}
    cv::Ptr<cv::Tracker> tracker = cv::TrackerMIL::createTracker();
    tracker->init(ref, DataManager::getDataManager().people[id]._roid);
    _trackers.insert(std::pair<int, cv::Ptr<cv::Tracker> >(id,tracker));
    _life.insert(std::pair<int, long >(id,0));
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

            _life[t->first]+=ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_STEP);

            if(_life[t->first]>ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_LIMIT_START)){

                if(_life[t->first] % ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_LIFE_LIMIT) == 0){
                    if(!recheckTracker(ref(DataManager::getDataManager().people[t->first]._roid))){
DataManager::getDataManager().people[t->first].trackCount = _TRACKER_REMOVED;
                _life.erase(_life.find(t->first));
                _trackers.erase(t);
 

                            }

                }
            
            cv::Rect2d res = rect &  roid;
            if(res.width < roid.width * tresh || res.height < roid.height * tresh){
            DataManager::getDataManager().people[t->first].trackCount = _TRACKER_REMOVED;
                _life.erase(_life.find(t->first));
                _trackers.erase(t);
                continue;
            }

            if(ConfigManager::getConfigManager().get<std::string>(ConfigManager::MD_METHOD) == PeopleDetector::GROUP_METHOD){
            if(TimeManager::getTimeManager().time() > ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_AVG_START)){
                if(DataManager::getDataManager().people[t->first]._roid.height < ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_AVG_TRASH) * DataManager::getDataManager().avgH || DataManager::getDataManager().people[t->first]._roid.width < ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_AVG_TRASH) * DataManager::getDataManager().avgW) {
                DataManager::getDataManager().people[t->first].trackCount = _TRACKER_REMOVED;
                _life.erase(_life.find(t->first));
                _trackers.erase(t);
 
                }
                
            }


        }



    }
}}}
