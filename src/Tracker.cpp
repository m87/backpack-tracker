#include "Tracker.h"

Tracker::Tracker(std::string method){
    MEMORY("Tracker created");

    if(method == "mil"){
        WARNING("Tracker: using MIL tracking methid");
       _method.reset(new MILTrackingMethod()); 
    }
}

Tracker::~Tracker(){
    MEMORY("Tracker destroyed");

}


