#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <map>
#include <yaml-cpp/yaml.h>
#include "TestCase.h"

class Benchmark
{
    std::map<std::string,TestCase> backpacksCases;
    std::map<std::string,TestCase> PeopleCases;
public:
    int people;
    int backpacks;
    Benchmark ();
    ~Benchmark ();
    void init();
    void perform();

};

#endif
