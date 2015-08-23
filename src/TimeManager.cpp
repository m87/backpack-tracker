#include "TimeManager.h"

TimeManager::TimeManager(){
    MEMORY("TimeManager created");
    _time = 0;

}

TimeManager & TimeManager::getTimeManager(){
        static TimeManager instance;
        return instance;
}

TimeManager::~TimeManager(){
    MEMORY("TimeManager deleted");
}

void TimeManager::tick(){
    _time++;

    VERBOSE_O("TimeManager: tick " + utils::str::to_string(_time));
}
long  TimeManager::time(){
    return _time;
}
