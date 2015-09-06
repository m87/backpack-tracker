#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "Utils.h"
#include <vector>

/** Pseudo-time manager based on frames counting*/
class TimeManager
{

    long _time;
    TimeManager ();

public:
    static TimeManager & getTimeManager();

    ~TimeManager ();
    ///increases time by 1
    void tick();
    ///returns current time
    long time();
    /**returns true on nth tick
     * @param n
     */
    bool checkStep(int n);
    /**returns true after nth frame
     */
    bool checkStart(int n);
};

#endif
