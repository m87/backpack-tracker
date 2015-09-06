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
    for(unsigned long i = 0; i < backpacks.size();i++){
        for(unsigned long j = 0; j < backpacks[i]._people.size();j++){
            if(people[backpacks[i]._people[j]].trackCount == -2){
                backpacks[i]._people.erase(backpacks[i]._people.begin()+j);
                        
            }

    }
}
for(auto i = people.begin(); i!=people.end(); i++){
    if(i->second.trackCount == -2){
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



