#include "DataManager.h"


DataManager::DataManager() : FrameBuffer(0){
  //  MEMORY("DataManager created");
}

DataManager::~DataManager(){
   // MEMORY("DataManager destroyed");
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
    stableBackpacks.clear();
}

std::vector<Group> DataManager::getGroups(){
    return groups;
}

void DataManager::addBacpack(Backpack backpack){
    backpacks.push_back(backpack);
}

std::vector<Backpack> DataManager::getBackpacks(){
    return backpacks;    

}



