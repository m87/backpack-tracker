#include "ConfigManager.h"

const int ConfigManager::CONFIG_NUM=10;
const string TEST_PATH = "test-path";
const string MOG_HIST = "mog-history";
const string MOG_MIXT = "mog-mixtures-num";
const string MOG_SHAD = "mog-shadow";
const string FRAMEW = "frame-width";
const string FRAMEH = "frame-height";
const string MOV_DILA = "mov-dilatation";
const string MOV_TRESH = "mov-treshold";
const string DET_STEP = "detection-step";

const string BLOBS = "blobs";

ConfigManager::ConfigManager(){
    
}

ConfigManager::ConfigManager(string path){
    _config = YAML::LoadFile(path);
    YAML::Node b = _config[BLOBS];
    for(size_t i=0;i<b.size();i++){
    blobs.push_back(b[i].as<string>());

}}

ConfigManager::ConfigManager(int argc, char *argv[]){

}

ConfigManager::~ConfigManager(){

}


