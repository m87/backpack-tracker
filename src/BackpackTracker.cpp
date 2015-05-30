#include <iostream>
#include <opencv2/opencv.hpp>
#include "preprocessor.h"
#include "ConfigManager.h"
#include "MovementDetector.h"
#include "PeopleDetector.h"
#include "Group.h"
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    namedWindow("capture", CV_WINDOW_AUTOSIZE);
    namedWindow("op", CV_WINDOW_AUTOSIZE);
    namedWindow("op2", CV_WINDOW_AUTOSIZE);
    namedWindow("op3", CV_WINDOW_AUTOSIZE);
    namedWindow("op4", CV_WINDOW_AUTOSIZE);



    MovementDetector mov(new ConfigManager(argv[1]));
    PeopleDetector people;

    while(true) {
        //prep.skipNFrames(1);
        vector<Group> group = mov.mog2Filter();
        Mat drawing;
        mov.getDebugView(0).copyTo(drawing);
        people.getPeopleROIs(mov.getDebugView(0),group);
        
        imshow("capture", mov.getDebugView(0));
        imshow("op", mov.getDebugView(2));
        imshow("op2", mov.getDebugView(3));
        imshow("op3", mov.getDebugView(4));
        imshow("op4", people.getDebugView(0));


        if (waitKey(20) >= 0)
            break;


    }

    return 0;
}
