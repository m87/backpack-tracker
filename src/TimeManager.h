#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#include "Utils.h"
#include <vector>

/** Pseudo-time manager */
class TimeManager
{
    long _time;

    TimeManager ();

public:
    static TimeManager & getTimeManager();

    ~TimeManager ();
    void tick();
    long time();
    bool checkStep(int step){ return !(_time % step) ;}
    bool checkStart(int step){ return (_time > step) ;}

};

#endif
