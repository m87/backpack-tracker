#include "MovementDetector.h"
const std::string MovementDetector::MOG_METHOD = "mog";
const std::string MovementDetector::KNN_METHOD = "knn";

MovementDetector::MovementDetector(std::string type){
    MEMORY("MovementDetector created");

    _type = type;
     
    if(type == MOG_METHOD){
        WARNING("MovementDetector: Using MOG method");
        mdMethod.reset(new MogMDMethod());
        mdMethod->initMethod(ConfigManager::getConfigManager());
    }
    if(type == KNN_METHOD){
        WARNING("MovementDetector: Using KNN method");
        mdMethod.reset(new KnnMDMethod());
        mdMethod->initMethod(ConfigManager::getConfigManager());
    }

}


MovementDetector::~MovementDetector(){
    MEMORY("MovementDetector destroyed");
}

void MovementDetector::detect(const cv::Mat& src){
    mdMethod->detect(src);
}
