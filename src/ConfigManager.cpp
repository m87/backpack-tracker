#include "ConfigManager.h"

const std::string ConfigManager::PREPROCESSOR_N_FRAMES = "preprocessor-frames-buffer-size";


const std::string ConfigManager::GPU = "gpu";
const std::string ConfigManager::FULL_TRACKING = "full-tracking";
const std::string ConfigManager::FACE_TRACKING = "face-tracking";
const std::string ConfigManager::BACKPACK_DETECTION = "backpack-detection";


const std::string ConfigManager::MD_METHOD = "md-method";
const std::string ConfigManager::MD_DETECTION_STEP = "md-detection-step";


const std::string ConfigManager::MD_MOG_HISTORY = "md-mog-history";
const std::string ConfigManager::MD_MOG_MIXTURES = "md-mog-mixtures";
const std::string ConfigManager::MD_MOG_SHADOW = "md-mog-shadow";
const std::string ConfigManager::MD_MOG_DILATATION = "md-mog-dilatation";
const std::string ConfigManager::MD_MOG_TRESHOLD = "md-mog-treshold";

const std::string ConfigManager::MD_KNN_HISTORY = "md-knn-history";
const std::string ConfigManager::MD_KNN_MIXTURES = "md-knn-mixtures";
const std::string ConfigManager::MD_KNN_SHADOW = "md-knn-shadow";
const std::string ConfigManager::MD_KNN_DILATATION = "md-knn-dilatation";
const std::string ConfigManager::MD_KNN_TRESHOLD = "md-knn-treshold";




const std::string ConfigManager::TEST_PATH = "test-path";
const std::string ConfigManager::MOG_HIST = "mog-history";
const std::string ConfigManager::MOG_MIXT = "mog-mixtures-num";
const std::string ConfigManager::MOG_SHAD = "mog-shadow";
const std::string ConfigManager::FRAMEW = "frame-width";
const std::string ConfigManager::FRAMEH = "frame-height";
const std::string ConfigManager::MOV_DILA = "mov-dilatation";
const std::string ConfigManager::MOV_TRESH = "mov-treshold";
const std::string ConfigManager::DET_STEP = "detection-step";

const std::string ConfigManager::BLOBS_ENABLE = "blobs-enable";
const std::string ConfigManager::BLOBS = "blobs";
const std::string ConfigManager::BLOBS_IMG = "blobs-img";
const std::string ConfigManager::BLOBS_W = "blobs-w";
const std::string ConfigManager::BLOBS_H = "blobs-h";
const std::string ConfigManager::BLOBS_X = "blobs-x";
const std::string ConfigManager::BLOBS_Y = "blobs-y";
const std::string ConfigManager::BLOBS_START = "blobs-start";
const std::string ConfigManager::BLOBS_TIME = "blobs-time";


const std::string ConfigManager::VIEW_FRAME_RESIZED = "view-frame-resized";
const std::string ConfigManager::VIEW_FRAME_REAL = "view-frame-real";
const std::string ConfigManager::VIEW_BLOBS = "view-blobs";
const std::string ConfigManager::VIEW_MOG_BACKGROUND = "view-mog-background";
const std::string ConfigManager::VIEW_MOG_FOREGROUND = "view-mog-foreground";
const std::string ConfigManager::VIEW_MOG_DILATATION = "view-mog-dilatation";
const std::string ConfigManager::VIEW_MOG_RESULT = "view-mog-result";

const std::string ConfigManager::VIEW_KNN_BACKGROUND = "view-knn-background";
const std::string ConfigManager::VIEW_KNN_FOREGROUND = "view-knn-foreground";
const std::string ConfigManager::VIEW_KNN_DILATATION = "view-knn-dilatation";
const std::string ConfigManager::VIEW_KNN_RESULT = "view-knn-result";


const std::string ConfigManager::VIEW_PD_RESULT = "view-pd-result";

ConfigManager::ConfigManager(){
    
    MEMORY("ConfigManager created");
    
}

ConfigManager& ConfigManager::getConfigManager(){
    static ConfigManager instance;
    return instance;
}

void ConfigManager::initConfigManager(std::string path){
    VERBOSE("ConfigManager: Using yaml-file: "+ path);
    VERBOSE("ConfigManager: Loading file ...");
   
    ConfigManager & configManager = getConfigManager();
    
    configManager._config = YAML::LoadFile(path);
    if(configManager.get<bool>(BLOBS_ENABLE)){
        WARNING("ConfigManager: Blobs enabled.");

        YAML::Node b = configManager._config[BLOBS];
        for(size_t i=0;i<b.size();i++){
            configManager.blobs.push_back(configManager._config[b[i].as<std::string>()]);
        }
    }else{
        WARNING("ConfigManager: Blobs disabled.");
              
    }

    WARNING("##########CONFIG##########");
    configManager.check(VIEW_FRAME_RESIZED);
    configManager.check(VIEW_FRAME_REAL);
    WARNING("##########END-CONFIG##########");



    VERBOSE("ConfigManager: File loaded");

}

void ConfigManager::check(std::string name){
    if(get<bool>(name)){
        INFO(name + ": enabled"); 
    }else{
        INFO(name + ": disabled"); 
    }
}



ConfigManager::~ConfigManager(){

    MEMORY("ConfigManager deleted");
}


