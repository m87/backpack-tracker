#include "Benchmark.h"


Benchmark::Benchmark() {
    MEMORY("Benchmark created");
    _backpacks = 0;
    _people = 0;

    _peopleStats.FP=0;
    _peopleStats.TP=0;
    _peopleStats.FN=0;
    _peopleStats.TN=0;

    _backpacksStats.FP=0;
    _backpacksStats.TP=0;
    _backpacksStats.TN=0;
    _backpacksStats.FN=0;
    init();
}

Benchmark::~Benchmark() {
    MEMORY("Benchmark destroyed");

}

void Benchmark::init() {
    VERBOSE("Benchmark: initialization");
    if(!ConfigManager::getConfigManager().get<bool>(ConfigManager::TEST_ENABLE)) {
        WARNING("Tests are disabled");
        return;
    }

    YAML::Node root = ConfigManager::getConfigManager().getTestRoot();
    YAML::Node keys = ConfigManager::getConfigManager().getTestRoot()[ConfigManager::TEST];
    for(unsigned long i = 0; i<keys.size(); i++) {
        TestCase test(keys[i].as<std::string>(), root[keys[i].as<std::string>()]["type"].as<std::string>(),root[keys[i].as<std::string>()]["x"].as<int>(),root[keys[i].as<std::string>()]["y"].as<int>(),root[keys[i].as<std::string>()]["width"].as<int>(),root[keys[i].as<std::string>()]["height"].as<int>(),root[keys[i].as<std::string>()]["time"].as<int>());
        if(test._type == TestCase::PERSON) {
            _people++;
            _peopleCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }
        if(test._type == TestCase::NO_PERSON) {
            _peopleCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }
        if(test._type == TestCase::BACKPACK)
        {
            _backpacks++;
            _backpacksCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }
        if(test._type == TestCase::NO_BACKPACK)
        {
            _backpacksCases.insert(std::pair<std::string, TestCase>(keys[i].as<std::string>(), test));
        }
    }
}

void Benchmark::perform() {
    VERBOSE_O("Benchmark: Performing tests");
    int FP = 0;
    int TP = 0;
    int FN = 0;
    int TN = 0;
    //people
    int FP_p = 0;
    int TP_p = 0;
    int FN_p = 0;
    int TN_p = 0;

    bool FN_pf = true;
    bool FP_pf = true;
    bool FN_f = true;
    bool FP_f = true;
    //if tests disabled
    if(!ConfigManager::getConfigManager().get<bool>(ConfigManager::TEST_ENABLE)) return;

    auto pMap = DataManager::getDataManager().people;
    auto bMap = DataManager::getDataManager().stableBackpacks;

    for(auto it2 = _peopleCases.begin(); it2!= _peopleCases.end(); it2++) {
        if(TimeManager::getTimeManager().time()!=it2->second._time) continue;
        if(it2->second._type == TestCase::PERSON) {
            FN_pf=true;
            FP_pf=false;
        }
        if(it2->second._type == TestCase::NO_PERSON) {
            FN_pf=false;
            FP_pf=true;
        }
        for(auto it = pMap.begin(); it != pMap.end(); it++) {
            if(it2->second._type == TestCase::PERSON) {
                if(utils::detect::checkOverlapping<double>(it->second._roid, it2->second._roi, ConfigManager::getConfigManager().get<double>(ConfigManager::TEST_ACC))) {
                    TP_p++;
                    FN_pf=false;
                }

            }
            if(it2->second._type == TestCase::NO_PERSON) {
                if(utils::detect::checkOverlapping<double>(it->second._roid, it2->second._roi, ConfigManager::getConfigManager().get<double>(ConfigManager::TEST_ACC))) {
                    FP_p++;
                    FP_pf=false;
                }


            }
        }
        if(FN_pf) FN_p++;
        if(FP_pf) TN_p++;
    }

    for(auto it2 = _backpacksCases.begin(); it2!= _backpacksCases.end(); it2++) {
        if(TimeManager::getTimeManager().time()!=it2->second._time) continue;
        if(it2->second._type == TestCase::BACKPACK) {
            FN_f=true;
            FP_f=false;
        }
        if(it2->second._type == TestCase::NO_BACKPACK) {
            FN_f=false;
            FP_f=true;
        }
        for(auto it = bMap.begin(); it != bMap.end(); it++) {
            if(it2->second._type == TestCase::BACKPACK) {
                if(utils::detect::checkOverlapping<double>(it->second.getRoi(), it2->second._roi, ConfigManager::getConfigManager().get<double>(ConfigManager::TEST_ACC))) {
                    TP++;
                    FN_f=false;
                }

            }
            if(it2->second._type == TestCase::NO_BACKPACK) {
                if(utils::detect::checkOverlapping<double>(it->second.getRoi(), it2->second._roi, ConfigManager::getConfigManager().get<double>(ConfigManager::TEST_ACC))) {
                    FP++;
                    FP_f=false;
                }


            }
        }
        if(FN_f) FN++;
        if(FP_f) TN++;


    }

    _peopleStats.FN+=FN_p;
    _peopleStats.TN+=TN_p;
    _peopleStats.FP+=FP_p;
    _peopleStats.TP+=TP_p;
    _backpacksStats.FN+=FN;
    _backpacksStats.TN+=TN;
    _backpacksStats.FP+=FP;
    _backpacksStats.TP+=TP;

}
