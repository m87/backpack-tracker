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

    Mat frameNew, frameLast, frameDiff, freamReal, frameTresh;
    Mat element,frameNoiseFree,blobs;

    BackgroundSubtractorMOG bg(500,200,false);
    BackgroundSubtractorGMG bgg;

    vector<vector<Point> > contours;
    prep.getFrame(frameLast,500.0f, -1.0f, true);
    while(true) {
        //prep.skipNFrames(1);
        prep.getFrame(frameNew,freamReal,500.0f,-1.0f,  true);

        //absdiff(frameLast,frameNew , frameDiff);
        bgg(frameNew,frameDiff) ;
        
        frameDiff.copyTo(frameNoiseFree);
        //prep.saveFrame(frameDiff);
        
        //prep.getAvgFrame(frameNoiseFree);
        
        //threshold(frameNoiseFree, frameTresh, 25, 255,0);

         
        //blur(frameTresh,frameTresh, Size(10,10));
        //threshold(frameTresh, frameTresh, 20, 255,0);

        

        /*frameDiff = frameLast - frameNew;
*/
//        element = prep.getStructuringElement(1,0);

//        morphologyEx(frameTresh, frameTresh, 1, element);




        imshow("capture", freamReal);
        imshow("op", frameNoiseFree);
        frameNew.copyTo(frameLast);

        
        if (waitKey(20) >= 0)
            break;


    }

    return 0;
}
