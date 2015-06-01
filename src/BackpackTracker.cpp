#include <iostream>
#include <opencv2/opencv.hpp>
#include "preprocessor.h"
#include "ConfigManager.h"
#include "MovementDetector.h"
#include "PeopleDetector.h"
#include "Group.h"
#include "Tracker.h"
#include <string>

using namespace std;
using namespace cv;

int maxCorners = 50;
vector<Point2f> corners, corners_prev,corners_tmp;
double qualityLevel = 0.01;
double minDistance=1;
int blockSize = 3;
bool useHarrisDetector = false;
double k  = 0.04;
vector<uchar> status;
vector<float> err;
float x_cord[100];
float y_cord[100];


int main(int argc, char *argv[])
{

//    namedWindow("capture", CV_WINDOW_AUTOSIZE);
    namedWindow("op", CV_WINDOW_AUTOSIZE);
  //  namedWindow("op2", CV_WINDOW_AUTOSIZE);
    //namedWindow("op3", CV_WINDOW_AUTOSIZE);
    //namedWindow("op4", CV_WINDOW_AUTOSIZE);



    MovementDetector mov(new ConfigManager(argv[1]));
    PeopleDetector people;
    Mat test;
    Tracker tracker;
    int kk=0;
    while(true) {
        //prep.skipNFrames(1);
        vector<Group> group = mov.mog2Filter();
        Mat drawing;
        mov.getDebugView(0).copyTo(drawing);
        vector<Person> p= people.getPeople(mov.getDebugView(0),group);
        tracker.update(p, mov.getDebugView(0));
        tracker.track(mov.getDebugView(0));
        tracker.print(mov.getDebugView(0));

        //imshow("capture", mov.getDebugView(0));
        //imshow("op", mov.getDebugView(2));
        imshow("op", tracker.getDebugView(0));
        //imshow("op2", mov.getDebugView(3));
        //imshow("op3", mov.getDebugView(4));
        //imshow("op4", people.getDebugView(0));


        if (waitKey(20) >= 0)
            break;


    }

    return 0;
}
