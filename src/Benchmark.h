#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <map>
#include <yaml-cpp/yaml.h>
#include "TestCase.h"
#include "Utils.h"
#include "ConfigManager.h"
#include "DataManager.h"
#include "TimeManager.h"

/**
 * Results structure
 */
struct stats {
    ///False-Positive
    int FP;
    ///True-Positive
    int TP;
    ///True-Negative
    int TN;
    ///False-Negative
    int FN;
};

/** Class for testing backpack detection and people tracking
 */
class Benchmark
{   
    //people counter
    int _people;
    //backpacks counter
    int _backpacks;
    //people detection test results
    stats _peopleStats;
    //backpacks detection test results
    stats _backpacksStats;
    //map of backpacks test cases
    std::map<std::string,TestCase> _backpacksCases;
    //map of people test cases
    std::map<std::string,TestCase> _peopleCases;
    void init();
public:
    Benchmark ();
    ~Benchmark ();
    //starts tests
    void perform();
    //shows results
    void show() {
        //People detection results
        INFO("Benchmark: People:\n\t FP: " + utils::str::to_string<int>(_peopleStats.FP)+"\n\t FN: " + utils::str::to_string<int>(_peopleStats.FN)+"\n\t TP: " + utils::str::to_string<int>(_peopleStats.TP)+"\n\t TN: " + utils::str::to_string<int>(_peopleStats.TN));
        //Backpacks detection results
        INFO("Benchmark: Backpacks:\n\t FP: " + utils::str::to_string<int>(_backpacksStats.FP)+"\n\t FN: " + utils::str::to_string<int>(_backpacksStats.FN)+"\n\t TP: " + utils::str::to_string<int>(_backpacksStats.TP)+"\n\t TN: " + utils::str::to_string<int>(_backpacksStats.TN));
        //Tests counter
        INFO("Benchmark: All:\n\tPeople: " + utils::str::to_string<int>(_people) + "\n\tBackpacks: " + utils::str::to_string(_backpacks));
    }

};

#endif
