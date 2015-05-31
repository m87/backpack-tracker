#ifndef PERSON_H
#define PERSON_H
#include <opencv2/opencv.hpp>

using namespace cv;

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

    vector<Point2f> _corners, _corners_prev, _corners_tmp;



public:
    Point center;
    long getID();
    Rect getROI();
    void updateROI();
    void reviewCorners();
    Person (Rect roi);
    ~Person ();
    void setCorners(vector<Point2f> corners);
    void setShift(int x, int y);
    void setCornersPrev(vector<Point2f> corners);
    vector<Point2f> getCorners();
    vector<Point2f> getCornersPrev();

};

#endif
