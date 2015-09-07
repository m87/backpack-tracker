#ifndef SESSION_H
#define SESSION_H

#include "Utils.h"
#include <memory>
#include "ConfigManager.h"
#include "TimeManager.h"
#include "BlobsGenerator.h"
#include "ViewsManager.h"
#include "Preprocessor.h"
#include "MovementDetector.h"
#include "PeopleDetector.h"
#include "BackpackDetector.h"
#include "UTracker.h"
#include <opencv2/highgui/highgui.hpp>
#include "Benchmark.h"

#define END_SESSION_KEY 113


/** Main class. Manages processing */
class Session
{
    /** Generates artificial objects */
    std::unique_ptr<BlobsGenerator> _blobsGenerator;
   /** Initializes main processing */
    std::unique_ptr<Preprocessor> _preprocessor;
    /** Movement detection */
    std::unique_ptr<MovementDetector> _movDetector;
    /** People detection*/
    std::unique_ptr<PeopleDetector> _peopleDetector;
    /** Backpack detection*/
    std::unique_ptr<BackpackDetector> _backpackDetector;
    /** Tracking */
    std::unique_ptr<UTracker> _tracker;
    /** Tests */ 
    Benchmark benchmark;

    bool OPENCV_ERROR;


public:
     Session ();
    ~Session ();
    void run();
    

};


#endif


