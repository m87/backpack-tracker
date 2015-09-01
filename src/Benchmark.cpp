#include "Benchmark.h"


Benchmark::Benchmark(){
    MEMORY("Benchmark created");
    backpacks = 0;
    people = 0;
    init();
}

Benchmark::~Benchmark(){
    MEMORY("Benchmark destroyed");

}

void Benchmark::init(){
    if(!ConfigManager::getConfigManager().get<bool>(ConfigManager::TEST_ENABLE)) return;

    YAML::Node root = ConfigManager::getConfigManager().getRoot();
    YAML::Node keys = ConfigManager::getConfigManager().getRoot()[ConfigManager::TEST];
    for(unsigned long i = 0; i<keys.size();i++){
        TestCase test(keys[i].as<std::string>(), root[keys[i].as<std::string>()]["type"].as<std::string>(),root[keys[i].as<string>()]["x"].as<int>(),root[keys[i].as<std::string>()]["y"].as<int>(),root[keys[i].as<std::string>()]["width"].as<int>(),root[keys[i].as<std::string>()]["height"].as<int>(),root[keys[i].as<std::string>()]["time"].as<int>());
        if(test._type == TestCase::PERSON) {
people++;

        PeopleCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }       
        if(test._type == TestCase::BACKPACK)
        {

            backpacks++;
        backpacksCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }

    }
}

void Benchmark::perform(){
    int FP = 0;
    int TP = 0;
    //people
    int P = 0;
    if(!ConfigManager::getConfigManager().get<bool>(ConfigManager::TEST_ENABLE)) return;
/*
    auto pMap = DataManager::getDataManager().people;
    auto bMap = DataManager::getDataManager().stableBackpacks;

    for(auto it = cases.begin(); it != cases.end();it++){
        if(it->second._type == TestCase::PERSON){
            //check;
           P++; 
        }
       }
     if(it->second._type == TestCase::BACKPACK){
            //check;
           TP++; 
           FP++; 
        }
*/

}
