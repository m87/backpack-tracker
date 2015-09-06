#include "UTracker.h"

UTracker::UTracker(std::string method) {
    MEMORY("UTracker created");

    if(method == "mil") {
        WARNING("UTracker: using MIL tracking methid");
        _method.reset(new MILTrackingMethod());
    }
    if(method == "median-flow") {
        WARNING("UTracker: using MediaFlow tracking methid");
        _method.reset(new MedianFlowTrackingMethod());
    }
    if(method == "boosting") {
        WARNING("UTracker: using Boosting tracking methid");
        _method.reset(new BoostingTrackingMethod());
    }
    if(method == "tld") {
        WARNING("UTracker: using TLD tracking methid");
        _method.reset(new TLDTrackingMethod());
    }
    if(method == "kalman") {
        WARNING("UTracker: using MIL tracking methid");
        _method.reset(new KalmanTrackingMethod());
    }
}

UTracker::~UTracker() {
    MEMORY("UTracker destroyed");

}


void UTracker::removeTracker(int id) {
    _method->removeTracker(id);
}

void UTracker::addTracker(int id, cv::Mat ref) {
    _method->addTracker(id,ref);
}

void UTracker::update(cv::Mat ref) {
    cv::Mat tmp;
    ref.copyTo(tmp);
    DataManager dm = DataManager::getDataManager();
    for(auto t=dm.people.begin(); t!=dm.people.end(); t++) {
        if(t->second.trackCount <= 0){
            DataManager::getDataManager().people[t->first].trackCount++;
            addTracker(t->first, ref);
        }



        try {
            rectangle(tmp, t->second._roid.tl(), t->second._roid.br(), cv::Scalar(0,255,0), 2,8,0);


        } catch(Exception e) {
        }

    }
    _method->update(ref);

    display(ConfigManager::VIEW_TRACKING_RESULT,tmp);

}

void UTracker::init() {
    _method->init();
}
