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
    /// security counter
    int countDown;
    /// patch image
    cv::Mat patchBase;
    std::vector<int> _people;
    void status();
    int _stableConfidance;
    int life;
    bool wasStable;
    bool saved;
    cv::Scalar getColor(); 
    bool destoyed;
    void patch(cv::Mat &dst);
    void overlayImage(const cv::Mat &background, const cv::Mat &foreground,
cv::Mat &output, cv::Point2i location);
    void incStableConfidance(int i);
    void takeSnapshot(int size, std::map<int, Person> people, double treshold, cv::Mat ref, std::string pathRuntime);
    bool isbase;
    int _stable;
    Backpack (cv::Rect roi, cv::Mat img, cv::Mat base, cv::Mat patch, int life, int countDown);
    Backpack();
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

        bool checkOverlapping(cv::Rect A, cv::Rect B, double treshold);

};

#endif
