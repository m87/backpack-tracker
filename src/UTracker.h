#ifndef UTRACKER_H
#define UTRACKER_H 
#include "cvcommon.h"
#include <opencv2/tracking/tracker.hpp>

#include "Person.h"

#include <vector>
using namespace std;
using namespace cv;
class UTracker
{
    /* data */
    vector<Person> _people;
    vector< Ptr<Tracker> > _trackers;
    

public:
    int kk;
    double fillLevel(Mat bg, Mat ref, Person p);
    bool hogGC(Mat ref, Person p);
    bool chechkOverlapping(Person p);
    UTracker ();
    ~UTracker ();
    void addPeople(vector<Person> people, Mat ref);
    Mat getDebugView(Mat ref);
    void update(Mat ref, Mat bg);

};

#endif
