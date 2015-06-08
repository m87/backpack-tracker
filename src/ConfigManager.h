#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <yaml-cpp/yaml.h>
using namespace std;

class ConfigManager
{
    /* data */
    static const int CONFIG_NUM;
    YAML::Node _config;
        
public:
    static const string TEST_PATH, MOG_HIST, MOG_MIXT, MOG_SHAD, FRAMEW, FRAMEH, MOV_DILA, MOV_TRESH, DET_STEP;

    ConfigManager ();
    ConfigManager (string config);
    ConfigManager(int argc, char *argv[]);
    template<typename T>
        T get(const string key){
            return _config[key].as<T>();
        }
    ~ConfigManager ();

};

#endif
