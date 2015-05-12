#include <iostream>
#include <opencv2/opencv.hpp>
#include "preprocessor.h"
#include <string>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{



    Preprocessor prep(argv[1],3);
    namedWindow("capture", CV_WINDOW_AUTOSIZE);
    namedWindow("op", CV_WINDOW_AUTOSIZE);

    Mat frameNew, frameLast, frameDiff, freamReal;
         


        prep.getFrame(frameNew,500.0f, -1.0f, true);
    while(true) {
        //prep.skipNFrames(1);
        frameNew.copyTo(frameLast);    
        prep.getFrame(frameNew,freamReal,500.0f,-1.0f,  true);
        frameDiff = frameLast - frameNew;

        
        prep.saveFrame(frameDiff);
        
        imshow("capture", freamReal);
        imshow("op", frameDiff);
        if (waitKey(20) >= 0)
          break;
        
        
    }

    return 0;
}
