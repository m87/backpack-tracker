#ifndef BLOB_GENERATOR_H
#define BLOB_GENERATOR_H
#include "cvcommon.h"
#include <vector>
#include "Blob.h"
#include "ViewInterface.h"

/** Generates artificial backpacks for testing */
class BlobsGenerator : public ViewInterface
{
    
    std::vector< std::unique_ptr<Blob> > blobs;
    cv::Mat _drawing;
public:
    BlobsGenerator ();
    ~BlobsGenerator ();
    /** merges all blobs with ref image */
    void merge(cv::Mat& ref);

};

#endif
