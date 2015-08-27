#include "KalmanTrackingMethod.h"

KalmanTrackingMethod::KalmanTrackingMethod(){
MEMORY("KalmanTrackingMethod created");
kk = 0;    

}

KalmanTrackingMethod::~KalmanTrackingMethod(){
MEMORY("KalmanTrackingMethod destroyed");

}

void KalmanTrackingMethod::init(){



}

void KalmanTrackingMethod::addTracker(int id, cv::Mat ref){
    
 //   cv::Ptr<cv::Tracker> tracker = cv::TrackerKalman::createTracker();
 //   tracker->init(ref, DataManager::getDataManager().people[id]._roid);
 //   _trackers.insert(std::pair<int, cv::Ptr<Tracker> >(id,tracker));
}

void KalmanTrackingMethod::update(cv::Mat ref){
 //   if(kk++ == 5){
 //   kk=0;
  //  for(auto t=_trackers.begin(); t!=_trackers.end();t++){
   //     t->second->update(ref,DataManager::getDataManager().people[t->first]._roid);
  //  }
 


}//}
