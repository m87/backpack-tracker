#ifndef BLOB_H
#define BLOB_H
#include "cvcommon.h"
#include "Utils.h"


/** artificial obejcts representation (for testing) */
class Blob
{
    static long ID;

public:
    cv::Mat _img;
    std::string _name;
    long _id;
    int _x,_y, _w, _h;
    long _start, _time;
    Blob (std::string name, cv::Mat img, int x, int y, int w, int h, long start, long time);
    ~Blob ();

};

#endif
