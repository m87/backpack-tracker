#ifndef BACKPACK_H
#define BACKPACK_H
#include "Utils.h"
#include "cvcommon.h"
#include <vector>
#include "FrameBuffer.h"

class Backpack
{
    static long ID;
    long _id;
    cv::Rect _roi;
    int _x,_y;

public:
    Backpack (cv::Rect roi, int x, int y);
    ~Backpack ();

};

#endif
