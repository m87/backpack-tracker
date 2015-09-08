#include "DataManager.h"


DataManager::DataManager() : FrameBuffer(0){
  //  MEMORY("DataManager created");
  n=0;
  avgW=0.0;
  avgH=0.0;
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
    //remove ids of people that aren`t tracked
    for(unsigned long i = 0; i < backpacks.size();i++){
        for(unsigned long j = 0; j < backpacks[i]._people.size();j++){
            if(people[backpacks[i]._people[j]].trackCount == _TRACKER_REMOVED){
                backpacks[i]._people.erase(backpacks[i]._people.begin()+j);
                        
            }

    }
}
    //remove people that aren`t tracked
for(auto i = people.begin(); i!=people.end(); i++){
    if(i->second.trackCount == _TRACKER_REMOVED){
        people.erase(i);
        break;
    }
}


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



