#include "UTracker.h"

UTracker::UTracker(std::string method){
    MEMORY("UTracker created");

    if(method == "mil"){
        WARNING("UTracker: using MIL tracking methid");
       _method.reset(new MILTrackingMethod()); 
    }
}

UTracker::~UTracker(){
    MEMORY("UTracker destroyed");

}



void UTracker::addTracker(int id, cv::Mat ref){
    _method->addTracker(id,ref);
}

void UTracker::update(cv::Mat ref){
    cv::Mat tmp;
    ref.copyTo(tmp);
    DataManager dm = DataManager::getDataManager();
    for(auto t=dm.people.begin(); t!=dm.people.end();t++){
        addTracker(t->first, ref);

        try{  rectangle(tmp, t->second._roid.tl(), t->second._roid.br(), cv::Scalar(0,255,0), 2,8,0);


    }catch(Exception e){
    }

    }
    _method->update(ref);

    imshow("tracker", tmp); 
 
}

void UTracker::init(){
    _method->init();
}
