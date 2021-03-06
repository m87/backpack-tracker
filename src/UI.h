#ifndef UI_H
#define UI_H
#include "cvcommon.h"
#include "DataManager.h"

/** User Interface class
 */
class UI
{

public:
    UI ();
    ~UI ();
    ///Matrices for final result presentation
    static cv::Mat FINAL, FINAL_CP;
    ///Active backpack
    static int pirintID;
    ///Mouse support
    static void callbackMouse(int event, int x ,int y , int flags, void* userdata);

 

};

#endif
