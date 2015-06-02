#ifndef MOVEMENT_DETECTOR_H
#define MOVEMENT_DETECTOR_H
#include "preprocessor.h"
#include "ConfigManager.h"
#include <opencv2/opencv.hpp>
#include "cvcommon.h"
#include <vector>
#include "Group.h"

using namespace std;
using namespace cv;

class MovementDetector
{
    
    Ptr<BackgroundSubtractor> _mog2;
    Preprocessor *_prep;
    ConfigManager *_config;
    Mat frameNew, frameLast, frameDiff, freamReal, frameTresh,framedd;
    Mat element,frameNoiseFree,blobs, frameDiff2, frameDiff3;
    Mat frameBg;
    
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int _step;
 
public:
    MovementDetector (ConfigManager *config);
    ~MovementDetector ();
    vector<vector<Point> > getMovementROIs();
    vector<Group> mog2Filter();
    Mat getDebugView(int i);     

};

#endif
