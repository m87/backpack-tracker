#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <string>
#include <yaml-cpp/yaml.h>
#include "cvcommon.h"

/** Yaml-based configuration manager. Stores all session settings */
class ConfigManager
{
    /** Config structure */
    YAML::Node _config;
    ConfigManager ();
    void check(std::string name);
       
public:
    /** Config keys */

    static const std::string GPU, FULL_TRACKING, FACE_TRACKING, BACKPACK_DETECTION, START;

    static const std::string TEST_PATH, MOG_HIST, MOG_MIXT, MOG_SHAD, FRAMEW, FRAMEH, MOV_DILA, MOV_TRESH, DET_STEP,BLOBS,BLOBS_IMG, BLOBS_W, BLOBS_H,BLOBS_X,BLOBS_Y, BLOBS_START, BLOBS_TIME, BLOBS_ENABLE,PREPROCESSOR_N_FRAMES;
    
    static const std::string MD_METHOD, MD_MOG_HISTORY, MD_MOG_MIXTURES, MD_MOG_SHADOW, MD_MOG_DILATATION, MD_MOG_TRESHOLD, MD_DETECTION_STEP;
    static const std::string MD_KNN_HISTORY, MD_KNN_MIXTURES, MD_KNN_SHADOW, MD_KNN_DILATATION, MD_KNN_TRESHOLD;
    
    static const std::string VIEW_FRAME_RESIZED, VIEW_FRAME_REAL, VIEW_BLOBS, VIEW_MOG_BACKGROUND, VIEW_MOG_FOREGROUND,  VIEW_MOG_DILATATION, VIEW_MOG_RESULT;
    static const std::string VIEW_KNN_BACKGROUND, VIEW_KNN_FOREGROUND,  VIEW_KNN_DILATATION, VIEW_KNN_RESULT, VIEW_PD_RESULT;
    static const std::string VIEW_BD_FOREGROUND, VIEW_BD_BACKGROUND, VIEW_BD_LONG_BG,VIEW_BD_DIFF_RESULT, VIEW_BD_RESULT;
    static const std::string VIEW_TRACKING_RESULT;

    static const std::string PD_METHOD;

    static const std::string BD_BUFFER, BD_MOG_HISTORY, BD_MOG_MIXTURES, BD_MOG_SHADOW, BD_KNN_HISTORY, BD_KNN_MIXTURES, BD_KNN_SHADOW, BD_BG_METHOD, BD_DIFF_TRESH, BD_OVERLAP_TRESH, BD_DM_TRESH, BD_DM_ERODE, BD_DM_DILATE, BD_BG_MOG_SHADOW,BD_BG_MOG_HISTORY, BD_BG_MOG_MIXTURES, BD_STABLE_TRESH, BD_STABLE_COST, BD_UNSTABLE_COST, BD_CHECKS_TRESH, BD_CONFIDANCE, BD_SNAPSHOT_SIZE, BD_MAIN_CONFIDANCE;
    
    static const std::string TRACKING_STEP;

    std::vector<YAML::Node> blobs;

    /** Values getter */
    template<typename T>
        T get(const std::string key){
            return ConfigManager::_config[key].as<T>();
        }

    static ConfigManager& getConfigManager();
    static void initConfigManager(std::string path);

    ~ConfigManager ();

};

#endif
