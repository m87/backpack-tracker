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

    cv::Mat _img;
    cv::Mat _base;
    int _confidence;
    int _checks;


public:
        bool isbase;
    int _stable;
    Backpack (cv::Rect roi, cv::Mat img, cv::Mat base);
    ~Backpack ();
    void incConfidence(int i =1);
    void incChecks(int i = 1);
    int getConfidence();
    int getChecks();
    cv::Mat getImg();
    cv::Mat getBase();
    long getID(); 
    cv::Rect getRoi();
    void setNewBase(cv::Mat base);

};

#endif
