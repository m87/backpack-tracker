#ifndef PERSON_H
#define PERSON_H
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class Person
{
    /* data */
    long _id;
    static long ID;
    Rect _roi;
    vector<uchar> _status;
    vector<float> _err;
    float _x_cord[100];
    float _y_cord[100];
    double accX;
    double accX2;
    double accY;
    double accY2;


    vector<bool> movBuff;
    int movBuffSize;

public:
    bool ROIOverlapping(Rect2d roid2);
    Rect2d _roid;
    vector<Point2f> _corners, _corners_prev, _corners_tmp;
    void error(bool er);
    bool isMoveing();
    Point center;
    long getID();
    Rect getROI();
    void updateROI(vector<uchar> _status);
    void reviewCorners();
    Person (Rect roi);
    ~Person ();
    void setCorners(vector<Point2f> corners);
    void setShift(int x, int y);
    void setCornersPrev(vector<Point2f> corners);
    vector<Point2f> getCorners();
    vector<Point2f> getCornersPrev();
    bool isInside(Point2f point);
    bool isOutside(Mat m);

};

#endif
