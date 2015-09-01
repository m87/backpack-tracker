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
     ///  enable/disable gpu
    static const std::string GPU, 
     ///  enable/disable tracking every person
                 FULL_TRACKING, 
     ///  enable/disable face tracking
                 FACE_TRACKING, 
     ///  enable/disable backpack detection
                 BACKPACK_DETECTION, 
     ///  start process after X frame
                 START;

     ///  path to config file
    static const std::string TEST_PATH, 
     ///  desired frame width 
                 FRAMEW, 
     ///  desired frame height
                 FRAMEH, 
     ///  skip X frames in people detection
                 DET_STEP,
     ///  list of defined blobs
                 BLOBS,
     ///  blob image
                 BLOBS_IMG, 
     ///  desired blob width
                 BLOBS_W, 
     ///  desired blob height
                 BLOBS_H,
     ///  desired blob x
                 BLOBS_X,
     ///  desired blob y
                 BLOBS_Y, 
     ///  display blob after X frames
                 BLOBS_START, 
     ///  display blob for X frames
                 BLOBS_TIME, 
     ///  enable/disable blobs
                 BLOBS_ENABLE,
     ///  size of preprocessor frame buffer @depreciated
                 PREPROCESSOR_N_FRAMES;
        /// motion detection method 
    static const std::string MD_METHOD, 
                /// history length in mog method 
                 MD_MOG_HISTORY, 
                 /// number of mixtures in mog method
                 MD_MOG_MIXTURES,
                 /// enable/disable shadow detection
                 MD_MOG_SHADOW, 
                 /// radius of dilatation kernel
                 MD_MOG_DILATATION, 
                 /// threshold 
                 MD_MOG_TRESHOLD, 
                 ///  
                 MD_DETECTION_STEP;
                 /// history length in knn method
    static const std::string MD_KNN_HISTORY, 
                 /// number of mixtures in knn method
                 MD_KNN_MIXTURES, 
                 /// enable/disable shadow detection
                 MD_KNN_SHADOW, 
                 /// radius of dilatation kernel
                 MD_KNN_DILATATION, 
                 /// threshold 
                 MD_KNN_TRESHOLD;
                 /// enable/disable resized frame view  
    static const std::string VIEW_FRAME_RESIZED, 
                 /// enable/disable real frame view 
                 VIEW_FRAME_REAL, 
                 /// enable/disable view after blobs generation
                 VIEW_BLOBS, 
                 /// enable/disable estimated background view
                 VIEW_MOG_BACKGROUND, 
                 /// enable/disable  estimated foreground view
                 VIEW_MOG_FOREGROUND,  
                 /// enable/disable  view after dilatation in movemenet detection
                 VIEW_MOG_DILATATION, 
                 /// enable/disable view of motion detection results
                 VIEW_MOG_RESULT;
                 /// enable/disable estimated background view
    static const std::string VIEW_KNN_BACKGROUND, 
                 /// enable/disable  estimated foreground view
                 VIEW_KNN_FOREGROUND,  
                 /// enable/disable  view after dilatation in movemenet detection
                 VIEW_KNN_DILATATION, 
                 /// enable/disable view of motion detection results
                 VIEW_KNN_RESULT, 
                 /// enable/disable people detection result view 
                 VIEW_PD_RESULT;
                 /// enable/disable  estimated foreground view (short estimation)
    static const std::string VIEW_BD_FOREGROUND, 
                 /// enable/disable  estimated background view (short estimation)
                 VIEW_BD_BACKGROUND, 
                 /// enable/disable  estimated background view (long estimation)
                 VIEW_BD_LONG_BG,
                 /// enable/disable estimations difference view
                 VIEW_BD_DIFF_RESULT, 
                 /// enable/disable backpack detection resutls view
                 VIEW_BD_RESULT;
                 /// enable/disable tracking results view 
    static const std::string VIEW_TRACKING_RESULT;
                 /// enable/disable final result view
    static const std::string VIEW_FINAL_RESULT;
                ///people detection method
    static const std::string PD_METHOD, 
                /// people ovelapping threshold  
                 PD_OVERLAP_TRESH;
                ///size of backpack detector's frame buffer
    static const std::string BD_BUFFER, 
                /// history length in mog method (short est.)
                 BD_MOG_HISTORY, 
                /// number of mixtures in mog method (short est.)
                 BD_MOG_MIXTURES, 
                /// enambel/disable shadow detection (short est.) 
                 BD_MOG_SHADOW, 
                /// history length in knn method (short est.)
                 BD_KNN_HISTORY, 
                /// number of mixtures in knn method (short est.)
                 BD_KNN_MIXTURES, 
                /// enambel/disable shadow detection (short est.) 
                 BD_KNN_SHADOW, 
                /// short estimation method type
                 BD_BG_METHOD, 
                /// Difference threshold (Backpack Detection)
                 BD_DIFF_TRESH, 
                /// backpacks ovelapping threshold  
                 BD_OVERLAP_TRESH, 
                /// noise reduction threshold  
                 BD_DM_TRESH, 
                /// noise reduction kernel radius (erosion) 
                 BD_DM_ERODE, 
                /// noise reduction kernel radius (dilatation) 
                 BD_DM_DILATE, 
                /// enambel/disable shadow detection (long est.) 
                 BD_BG_MOG_SHADOW,
                /// history length in mog method (long est.)
                 BD_BG_MOG_HISTORY, 
                /// number of mixtures in mog method (long est.)
                 BD_BG_MOG_MIXTURES, 
                /// time when backpacks becomes stable (probably it is backpack) 
                 BD_STABLE_TRESH, 
                /// cost of losing stabilty  
                 BD_STABLE_COST, 
                /// cost of losing confidace 
                 BD_UNSTABLE_COST, 
                /// time whem difference changes stabilty 
                 BD_CHECKS_TRESH, 
                /// number of frames which generates proper diff 
                 BD_CONFIDANCE, 
                 /// size of window where are possible owners
                 BD_SNAPSHOT_SIZE, 
                 /// final confidace dispalyed in human-friendly format
                 BD_MAIN_CONFIDANCE, 
                /// enable/disable text above backpacks 
                 BD_ID_TEXT, 
                /// threshold of snapshot window and person overlapping 
                 BD_SNAPSHOT_TRESH;
                /// number of frames to skip 
    static const std::string TRACKING_STEP;

                /// test cases list
                static const std::string TEST,
                             /// enable/disable tests 
                             TEST_ENABLE;

static const std::string BD_STABLE_CONF_TRESH;

    std::vector<YAML::Node> blobs;

    /** Values getter */
    template<typename T>
        T get(const std::string key){
            return ConfigManager::_config[key].as<T>();
        }

    static ConfigManager& getConfigManager();
    static void initConfigManager(std::string path);

    ~ConfigManager ();
    YAML::Node getRoot(){ return _config; }

};

#endif
