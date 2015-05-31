#ifndef TRACKER_H
#define TRACKER_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Person.h"

using namespace std;
using namespace cv;

class Tracker
{
    /* data */
    vector<Person> _people;
    Mat _test;
    Mat _ref_prev;
    Mat _ref;
    static int maxCorners;
    static double qualityLevel;
    static double minDistance;
    static int blockSize;
    static bool useHarrisDetector;
    static double k;
  bool flag; 
public:
    Tracker ();
    ~Tracker ();
    bool isTracked(vector<Point2f> corners);
    bool isInside(Point2f point, Rect roi);

    vector< Person > track( Mat ref);
    void update(vector<Person> people, Mat ref);
    Mat getDebugView(int i); 
    void addPerson(Person person);
    void print(Mat ref);
    


};

#endif
