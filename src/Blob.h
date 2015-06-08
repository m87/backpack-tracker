#ifndef BLOB_H
#define BLOB_H
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Blob
{
    /* data */

public:
    Mat _img;
    string _name;
    Blob (string name);
    ~Blob ();

};

#endif
