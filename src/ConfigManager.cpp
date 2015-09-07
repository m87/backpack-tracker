#include "ConfigManager.h"

const std::string ConfigManager::PREPROCESSOR_N_FRAMES = "preprocessor-frames-buffer-size";
const std::string ConfigManager::GPU = "gpu";
const std::string ConfigManager::FULL_TRACKING = "full-tracking";
const std::string ConfigManager::FACE_TRACKING = "face-tracking";
const std::string ConfigManager::BACKPACK_DETECTION = "backpack-detection";
const std::string ConfigManager::START = "start";
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
const std::string ConfigManager::PD_METHOD = "pd-method";
const std::string ConfigManager::PD_OVERLAP_TRESH = "pd-overlap-treshold";
const std::string ConfigManager::BD_BUFFER = "bd-buffer";
const std::string ConfigManager::BD_BG_METHOD = "bd-bg-method";
const std::string ConfigManager::BD_MOG_SHADOW = "bd-mog-shadow";
const std::string ConfigManager::BD_MOG_HISTORY = "bd-mog-history";
const std::string ConfigManager::BD_MOG_MIXTURES = "bd-mog-mixtures";
const std::string ConfigManager::BD_KNN_SHADOW = "bd-knn-shadow";
const std::string ConfigManager::BD_KNN_HISTORY = "bd-knn-history";
const std::string ConfigManager::BD_KNN_MIXTURES = "bd-knn-mixtures";
const std::string ConfigManager::BD_DIFF_TRESH = "bd-diff-treshold";
const std::string ConfigManager::BD_OVERLAP_TRESH = "bd-overlap-treshold";
const std::string ConfigManager::BD_ID_TEXT = "bd-id-text";
const std::string ConfigManager::BD_COUNT_DOWN = "bd-count-down";
const std::string ConfigManager::BD_BACKPACK_LIFE = "bd-backpack-life";
const std::string ConfigManager::BD_DM_TRESH = "bd-dm-treshold";
const std::string ConfigManager::BD_DM_ERODE = "bd-dm-erode";
const std::string ConfigManager::BD_DM_DILATE = "bd-dm-dilate";
const std::string ConfigManager::BD_BG_MOG_SHADOW = "bd-bg-mog-shadow";
const std::string ConfigManager::BD_BG_MOG_HISTORY = "bd-bg-mog-history";
const std::string ConfigManager::BD_BG_MOG_MIXTURES = "bd-bg-mog-mixtures";
const std::string ConfigManager::BD_STABLE_TRESH = "bd-dm-stable-threshold";
const std::string ConfigManager::BD_STABLE_COST = "bd-dm-stable-cost";
const std::string ConfigManager::BD_UNSTABLE_COST = "bd-dm-unstable_cost";
const std::string ConfigManager::BD_CHECKS_TRESH = "bd-dm-checks-threshold";
const std::string ConfigManager::BD_CONFIDANCE = "bd-dm-confidance";
const std::string ConfigManager::BD_MAIN_CONFIDANCE = "bd-dm-main-confidance";
const std::string ConfigManager::BD_SNAPSHOT_SIZE = "bd-snapshot-size";
const std::string ConfigManager::BD_SNAPSHOT_TRESH = "bd-snapshot-treshold";
const std::string ConfigManager::BD_OVERLAP_PEOPLE_TRESH = "bd-overlap-people-treshold";
const std::string ConfigManager::TRACKING_STEP = "tracking-step";
const std::string ConfigManager::TEST_PATH = "test-path";
const std::string ConfigManager::FRAMEW = "frame-width";
const std::string ConfigManager::FRAMEH = "frame-height";
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
const std::string ConfigManager::VIEW_BD_FOREGROUND = "view-bd-foreground";
const std::string ConfigManager::VIEW_BD_BACKGROUND = "view-bd-background";
const std::string ConfigManager::VIEW_BD_LONG_BG = "view-bd-long-bg";
const std::string ConfigManager::VIEW_BD_DIFF_RESULT = "view-bd-diff-result";
const std::string ConfigManager::VIEW_BD_RESULT = "view-bd-result";
const std::string ConfigManager::VIEW_TRACKING_RESULT = "view-tracking-result";
const std::string ConfigManager::VIEW_FINAL_RESULT = "view-final-result";
const std::string ConfigManager::TEST = "test";
const std::string ConfigManager::TEST_ENABLE = "test-enable";
const std::string ConfigManager::TEST_ACC = "test-acc";
const std::string ConfigManager::BD_STABLE_CONF_TRESH = "bd-stable-conf-tresh";
const std::string ConfigManager::TRACKING_LIMIT = "tracking-limit";
const std::string ConfigManager::TRACKING_TRESH = "tracking-tresh";
const std::string ConfigManager::TRACKING_MERGE_TRESH = "tracking-merge-tresh";
const std::string ConfigManager::TRACKING_METHOD = "tracking-method";
const std::string ConfigManager::TESTS_SRC = "test-source";
const std::string ConfigManager::BLOBS_SRC = "blobs-source";
const std::string ConfigManager::RUNTIME = "runtime";

bool ConfigManager::CONFIG_ERROR = false;

ConfigManager::ConfigManager() {

  //  MEMORY("ConfigManager created");

}


ConfigManager& ConfigManager::getConfigManager() {
    static ConfigManager instance;
    return instance;
}

void ConfigManager::initConfigManager(std::string path) {
    VERBOSE("ConfigManager: Using yaml-file: "+ path);
    VERBOSE("ConfigManager: Loading file ...");

    ConfigManager & configManager = getConfigManager();


    try {
        configManager._config = YAML::LoadFile(path);
    } catch(...) {
        ERROR("Config file error");
        CONFIG_ERROR = true;
    }


    try {
        configManager._tests = YAML::LoadFile(configManager._config[ConfigManager::TESTS_SRC].as<std::string>());
    } catch(...) {
        ERROR("Tests file error");
        CONFIG_ERROR = true;
    }

    try {
        configManager._blobs = YAML::LoadFile(configManager._config[ConfigManager::BLOBS_SRC].as<std::string>());
    } catch(...) {
        ERROR("Blobs file error");
        CONFIG_ERROR = true;
    }




    if(configManager.get<bool>(BLOBS_ENABLE)) {
        WARNING("ConfigManager: Blobs enabled.");

        YAML::Node b = configManager._blobs[BLOBS];
        for(size_t i=0; i<b.size(); i++) {
            configManager.blobs.push_back(configManager._blobs[b[i].as<std::string>()]);
        }
    } else {
        WARNING("ConfigManager: Blobs disabled.");

    }

    WARNING("##########CONFIG##########");
    configManager.check(VIEW_FRAME_RESIZED);
    configManager.check(VIEW_FRAME_REAL);
    configManager.check(VIEW_FRAME_RESIZED);
    configManager.check(VIEW_FRAME_REAL);
    configManager.check(VIEW_BLOBS);
    configManager.check(VIEW_MOG_BACKGROUND);
    configManager.check(VIEW_MOG_FOREGROUND);
    configManager.check(VIEW_MOG_DILATATION);
    configManager.check(VIEW_MOG_RESULT);
    configManager.check(VIEW_KNN_BACKGROUND);
    configManager.check(VIEW_KNN_FOREGROUND);
    configManager.check(VIEW_KNN_DILATATION);
    configManager.check(VIEW_KNN_RESULT);
    configManager.check(VIEW_PD_RESULT);
    configManager.check(VIEW_BD_FOREGROUND);
    configManager.check(VIEW_BD_BACKGROUND);
    configManager.check(VIEW_BD_LONG_BG);
    configManager.check(VIEW_BD_DIFF_RESULT);
    configManager.check(VIEW_BD_RESULT);
    configManager.check(VIEW_TRACKING_RESULT);
    configManager.check(VIEW_FINAL_RESULT);

    WARNING("##########END-CONFIG##########");



    VERBOSE("ConfigManager: File loaded");

}

void ConfigManager::check(std::string name) {
    if(get<bool>(name)) {
        INFO(name + ": enabled");
    } else {
        INFO(name + ": disabled");

    }
}

ConfigManager::~ConfigManager() {

//    MEMORY("ConfigManager deleted");
}


