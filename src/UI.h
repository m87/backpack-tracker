#ifndef UI_H
#define UI_H
#include "cvcommon.h"

class UI
{

public:
    UI ();
    ~UI ();
    //Matrices for final result presentation
    static cv::Mat FINAL, FINAL_CP;
    //Active backpack
    static int pirintID;
    static void callbackMouse(int event, int x ,int y , int flags, void* userdata);

 

};

#endif
