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

ConfigManager::ConfigManager(){
    
}

ConfigManager::ConfigManager(string path){
   /* ifstream in(path.c_str());   
    string args[CONFIG_NUM];
    in >> args[0] >> args[1] >> args[2] >> args[3]
        >> args[4] >> args[5] >> args[6]
        >> args[7] >> args[8] ;
    _srcPath = args[0];
    _MOGHistory = std::atoi(args[1].c_str());
    _MOGNMixtures = std::atoi(args[2].c_str());
    _MOGShadows = std::atoi(args[3].c_str());
    _opFrameX = std::atof(args[4].c_str());
    _opFrameY = std::atof(args[5].c_str());
    _firstStageDilatation = std::atoi(args[6].c_str());
    _firstStageTreshold = std::atoi(args[7].c_str());
    _detectionStep = std::atoi(args[8].c_str());
   */
    _config = YAML::LoadFile(path);
    

}

ConfigManager::ConfigManager(int argc, char *argv[]){

}

ConfigManager::~ConfigManager(){

}


