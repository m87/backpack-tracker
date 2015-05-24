#include "ConfigManager.h"

const int ConfigManager::CONFIG_NUM=10;

ConfigManager::ConfigManager(){

}

ConfigManager::ConfigManager(string path){
    ifstream in(path.c_str());    
    string args[CONFIG_NUM];
    in >> args[0] >> args[1] >> args[2] >> args[3]
        >> args[4] >> args[5] >> args[6]
        >> args[7];
}

ConfigManager::ConfigManager(int argc, char *argv[]){

}

ConfigManager::~ConfigManager(){

}


