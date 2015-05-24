#include <iostream>
#include <opencv2/opencv.hpp>
#include "preprocessor.h"
#include "ConfigManager.h"
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    ConfigManager config(argv[1]);
    Preprocessor prep(config._srcPath,3);
    namedWindow("capture", CV_WINDOW_AUTOSIZE);
    namedWindow("op", CV_WINDOW_AUTOSIZE);
    namedWindow("op2", CV_WINDOW_AUTOSIZE);
    namedWindow("op3", CV_WINDOW_AUTOSIZE);
    namedWindow("op4", CV_WINDOW_AUTOSIZE);

    Mat frameNew, frameLast, frameDiff, freamReal, frameTresh,framedd;
    Mat element,frameNoiseFree,blobs, frameDiff2, frameDiff3;
    Mat frameBg;
    BackgroundSubtractorMOG2 bg(config._MOGHistory,config._MOGNMixtures,config._MOGShadows);
    BackgroundSubtractorGMG bgg;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;


    prep.getFrame(frameLast,config._opFrameX, config._opFrameY, true);

    while(true) {
        //prep.skipNFrames(1);
        prep.getFrame(frameNew,freamReal,config._opFrameX, config._opFrameY,  true);
        prep.getFrame(frameBg,config._opFrameX, config._opFrameY,  false);

        bg(frameBg,frameDiff) ;
        bg.getBackgroundImage(frameBg);
          
        cvtColor(frameBg,frameBg,CV_RGB2GRAY);

        absdiff(frameBg,frameNew , frameDiff2);
       
        element = prep.getStructuringElement(config._firstStageDilatation,0);
        bitwise_and(frameDiff,frameDiff2,frameDiff3,Mat());
        threshold(frameDiff3, frameDiff3, config._firstStageTreshold, 255,0);
        //absdiff(frameDiff,frameDiff2 , frameDiff3);

       
        
        frameDiff.copyTo(frameNoiseFree);
        prep.saveFrame(frameDiff2);
        dilate(frameDiff3,frameDiff3, element);
        //morphologyEx(frameDiff3, frameDiff3, 1, element);
        
    findContours( frameDiff3, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)  );

    vector<Rect> boundRect(contours.size());
    vector<vector<Point> > contoursPoly(contours.size());
Mat drawing;
frameNew.copyTo(drawing);
  for( unsigned long i = 0; i< contours.size(); i++  )
  {
      approxPolyDP(Mat(contours[i]),contoursPoly[i],10,false);
      
      boundRect[i] = boundingRect(Mat(contoursPoly[i]));
  }

  for( unsigned long i = 0; i< contours.size(); i++  )
  {
      Scalar color = Scalar(255,0,0);
      rectangle(drawing, boundRect[i].tl(),boundRect[i].br(),color,2,8,0);
                         
  }

        //prep.getAvgFrame(frameNoiseFree);
        

         
        //blur(frameTresh,frameTresh, Size(10,10));
        //threshold(frameTresh, frameTresh, 20, 255,0);

        

        /*frameDiff = frameLast - frameNew;
*/



        imshow("capture", freamReal);
        imshow("op", frameNoiseFree);
        imshow("op2", frameBg);
        imshow("op3", frameDiff3);
        imshow("op4", drawing);
        frameNew.copyTo(frameLast);

        
        if (waitKey(20) >= 0)
            break;


    }

    return 0;
}
