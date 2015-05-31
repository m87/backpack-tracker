#ifndef PEOPLE_DETECTOR_H
#define PEOPLE_DETECTOR_H

#include <opencv2/opencv.hpp>
#include "Group.h"
#include "Person.h"

using namespace cv;

class PeopleDetector
{
    /* data */
    Mat drawing;
    HOGDescriptor hog;


public:
    PeopleDetector ();
    ~PeopleDetector ();

    vector<Person> getPeople(Mat ref, vector<Group> group);

    vector<vector<Rect> > getPeopleROIs(Mat ref, vector<Group> group);
    Mat getDebugView(int i);

};

#endif
