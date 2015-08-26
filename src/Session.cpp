#include "Session.h"


Session::Session(){
    MEMORY("Session created");
    OPENCV_ERROR = false;
    ConfigManager config = ConfigManager::getConfigManager();
    try{

        ViewsManager::getViewsManager().reset();

        if(config.get<bool>(ConfigManager::BLOBS_ENABLE)){
           _blobsGenerator.reset(new BlobsGenerator());
            WARNING("Blobs enabled");

        }else{
            WARNING("Blobs disabled");
        }

        _preprocessor.reset(new Preprocessor(config.get<std::string>(ConfigManager::TEST_PATH),
                    config.get<unsigned long>(ConfigManager::PREPROCESSOR_N_FRAMES)));

        _peopleDetector.reset(new PeopleDetector());


        SESSION("New session created!");

    }catch(cv::Exception e){
        ERROR("OpenCV exception " + e.msg);
        SESSION("Session error!");
        OPENCV_ERROR = true;
    }


    _movDetector.reset(new MovementDetector(config.get<std::string>(ConfigManager::MD_METHOD)));
    _backpackDetector.reset(new BackpackDetector());

    _tracker.reset(new UTracker("mil"));


}

Session::~Session(){
    
    MEMORY("Session deleted");
}

void Session::filterGroups(){
    
}

void Session::filterPeople(){

}

void Session::filterBackpacks(){

}


void Session::run(){

    int frameWidth = ConfigManager::getConfigManager().get<int>(ConfigManager::FRAMEW);
    int frameHeight = ConfigManager::getConfigManager().get<int>(ConfigManager::FRAMEH);

    if(OPENCV_ERROR){
        return;
    }else{
        SESSION("Session started!");
    }

    //DataManager::getDataManager().setSize(20);
    //DataManager::getDataManager().setSize(20);
    DataManager::getDataManager().setSize(ConfigManager::getConfigManager().get<int>(ConfigManager::BD_BUFFER));
    DataManager::getDataManager().setSize(ConfigManager::getConfigManager().get<int>(ConfigManager::BD_BUFFER));


    while(true){
        TimeManager::getTimeManager().tick();


        Mat out, out1,tt; 
        _preprocessor->getFrame(tt,out1,frameWidth,frameHeight,false);
        tt.copyTo(out);
        cvtColor(out,out,cv::COLOR_RGB2GRAY);
        _blobsGenerator->merge(out);

        //DataManager::getDataManager().addFrame(out);

        _movDetector->detect(out);
        

        if(TimeManager::getTimeManager().checkStep(ConfigManager::getConfigManager().get<int>(ConfigManager::DET_STEP))){

        _peopleDetector->detect(out);
        }
        _tracker->update(tt);    
        
        /*        
        if(ConfigManager::getConfigManager().get<bool>(ConfigManager::BACKPACK_DETECTION)){
            _backpackDetector->detect(out);
            filterBackpacks(); // distinct //remove also from current flow already processed
        }

        }
 */ 
        /*if(ConfigManager::getConfigManager().get<bool>(ConfigManager::BACKPACK_DETECTION)){
            _backpackDetector->detect(out);
            filterBackpacks(); // distinct //remove also from current flow already processed
        }
*/

        DataManager::getDataManager().clean();
        


        ViewsManager::getViewsManager().showAll();

        if(END_SESSION_KEY == waitKey(10)){
            INFO("Key captured!");
            SESSION("Stopping session ...");
            break;
        }


    }
   
    
    SESSION("Session stopped!");

}


