#ifndef GROUP_H
#define GROUP_H
#include <opencv2/opencv.hpp>

using namespace cv;

class Group
{
    /* data */
    double _widthScale;
    double _heightScale;
    double _relativeX;
    double _relativeY;
    Mat _img;
    Mat _estimation;

public:
    double getWidthScale();
    double getHeightScale();
    double getRelativeX();
    double getRelativeY();
    Mat getImg();
    Mat getEst();
    Group (double widthScale, double heightScale, double relativeX, double relativeY, Mat img);
    Group (double widthScale, double heightScale, double relativeX, double relativeY, Mat img, Mat estimation);
    Group (double widthScale, double heightScale, double relativeX, double relativeY);
    ~Group ();

};
#endif
