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

#define END_SESSION_KEY 113


/** Main class. Manages processing */
class Session
{
    /** Generates artificial objects */
    std::unique_ptr<BlobsGenerator> _blobsGenerator;
   /** Initializes main processing */
    std::unique_ptr<Preprocessor> _preprocessor;
    /** All managers are global */
    std::unique_ptr<MovementDetector> _movDetector;
    
    std::unique_ptr<PeopleDetector> _peopleDetector;

    std::unique_ptr<BackpackDetector> _backpackDetector;
    std::unique_ptr<UTracker> _tracker;
 

    bool OPENCV_ERROR;

    void filterGroups();
    void filterPeople();
    void filterBackpacks();

public:
     Session ();
    ~Session ();
    void run();
    

};


#endif


