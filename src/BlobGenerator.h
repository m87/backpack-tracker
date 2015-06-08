#ifndef BLOB_GENERATOR_H
#define BLOB_GENERATOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Blob.h"

using namespace cv;
using namespace std;

class BlobGenerator
{
    /* data */
    vector<Blob> blobs;

public:
    BlobGenerator ();
    ~BlobGenerator ();
    void print(Mat ref);

};

#endif
