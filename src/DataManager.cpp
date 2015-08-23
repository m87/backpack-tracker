#include "DataManager.h"


DataManager::DataManager() : FrameBuffer(0){
    MEMORY("DataManager created");
}

DataManager::~DataManager(){
    MEMORY("DataManager destroyed");
}


DataManager & DataManager::getDataManager(){
    static DataManager instance;
    return instance;
}

void DataManager::addGroup(Group group){
    groups.push_back(group);
}

void DataManager::clean(){
    groups.clear();
}

std::vector<Group> DataManager::getGroups(){
    return groups;
}
