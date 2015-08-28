#ifndef BACKPACK_H
#define BACKPACK_H
#include <vector>
#include "FrameBuffer.h"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <memory>
#include "Utils.h"
#include <map>
#include "Person.h"

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
    std::vector<int> _people;
    int _stableConfidance;
    bool saved;
    cv::Scalar getColor(); 

    bool checkOverlapping(cv::Rect A, cv::Rect B);
    void incStableConfidance(int i);
    void takeSnapshot(int size, std::map<int, Person> people);
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
    void shrink(cv::Mat sum);

};

#endif
