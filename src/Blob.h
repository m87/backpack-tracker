#ifndef BLOB_H
#define BLOB_H
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Blob
{
    /* data */
    static long ID;

public:
    Mat _img;
    string _name;
    long _id;
    int _x,_y;
    long _start, _time;
    Blob (string name, Mat img, int x, int y, long start, long time);
    ~Blob ();

};

#endif
