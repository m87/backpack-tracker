#ifndef GROUP_H
#define GROUP_H
#include "cvcommon.h"
#include "Utils.h"

/** Group of moving objects. For hog eficiency in low crowded areas
 *  @see PeopleDetector
 */
class Group
{
    double _widthScale;
    double _heightScale;
    double _relativeX;
    double _relativeY;
    cv::Mat _img;
    cv::Mat _estimation;
    cv::Rect _roi;

public:
    cv::Rect getRoi();
    double getWidthScale();
    double getHeightScale();
    double getRelativeX();
    double getRelativeY();
    cv::Mat getImg();
    cv::Mat getEst();
    Group (double widthScale, double heightScale, double relativeX, double relativeY, cv::Mat img);
    Group (double widthScale, double heightScale, double relativeX, double relativeY, cv::Mat img, cv::Mat estimation, cv::Rect roi);
    Group (double widthScale, double heightScale, double relativeX, double relativeY);
    ~Group ();

};
#endif
