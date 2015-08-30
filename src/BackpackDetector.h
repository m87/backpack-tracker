#ifndef BACKPACK_DETECTOR_H
#define BACKPACK_DETECTOR_H
#include "cvcommon.h"
#include "ViewInterface.h"
#include <opencv2/highgui/highgui.hpp>
#include "UI.h"

/** Detects backpacks and binds people with backpackas.
 *  @see ViewInterface showing results
 *  @see UI using mouse
 * */
class BackpackDetector : public ViewInterface, UI {
    //Background estimation methods
    const static std::string BG_MOG_METHOD, BG_KNN_METHOD;
    //Estimation with short history
    cv::Ptr<cv::BackgroundSubtractor> _mog2;
    //Estimation with longer history
    cv::Ptr<cv::BackgroundSubtractor> _bgLong;
    cv::Mat bg;

public:

    /** Setups UI elements and background estimation
     *  @see ConfigManager::BD_MOG_SHADOW
     *  @see ConfigManager::BD_MOG_HISTORY
     *  @see ConfigManager::BD_MOG_MIXTURES
     *  @see ConfigManager::BD_KNN_SHADOW
     *  @see ConfigManager::BD_KNN_HISTORY
     *  @see ConfigManager::BD_KNN_MIXTURES
     *  @see ConfigManager::BD_BG_METHOD
     * */
    BackpackDetector ();
    ~BackpackDetector ();

    /** Triggers detection */
    void detect(cv::Mat ref);
    /** Updates estimation with longer history */
    void update(cv::Mat ref);
    /** Basic backpacks extraction method. Using difference between long and short backgroun estimation results. For better results usese agregated difference.
     *
     * @see ConfigManager::BD_DM_TRESH
     * @see ConfigManager::BD_DM_TRESH
     * @see ConfigManager::BD_DM_ERODE
     * @see ConfigManager::BD_DM_DILATE
     * @see ConfigManager::BD_BUFFER
     * @see ConfigManager::BD_UNSTABLE_COST
     * @see ConfigManager::BD_STABLE_TRESH
     * @see ConfigManager::BD_STABLE_COST
     * @see ConfigManager::BD_CHECKS_TRESH
     * @see ConfigManager::BD_CONFIDANCE
     * @see ConfigManager::BD_MAIN_CONFIDANCE
     * @see ConfigManager::BD_ID_TEXT
     * @see Backpack
     */
    void bgDiffMethod(cv::Mat ref);
    /** Checks overlapping of two Rectangles
     * @parm type true - Compare with As dimensions, false - Compare with Bs dimensions
     * @see ConfigManager::BD_OVERLAP_TRESH
     * */
    bool checkOverlapping(cv::Rect A, cv::Rect B, bool type);

    /** Checks difference level
     *  @param diff result of Matrieces subtraction or absdiff
     *  @return true if difference is higher than required level defined in config file
     *  @see ConfigMaanger::BD_DIFF_TRESH
     */
    bool checkDiff(cv::Mat diff);


};
#endif
