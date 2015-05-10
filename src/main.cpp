#include <iostream>
#include <opencv2/opencv.hpp>
#include "preprocessor.h"
#include <string>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    Preprocessor prep(argv[1]);

    Mat past;
    Mat now;

    namedWindow("capture", CV_WINDOW_AUTOSIZE);
    namedWindow("op", CV_WINDOW_AUTOSIZE);

    BackgroundSubtractorMOG2 fgbg(300,64,false);
    Mat out, out1; 
    prep.getFrame(out);
    prep.getFrame(out1);

    Mat element = getStructuringElement(0,Size(3,3),Point(1,1));
   Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3,3) );   
    
    while(true){
        prep.getFrame(now);
        fgbg(now,past,-1);
       // threshold(past, out, 130,255,0);
        //dilate(past,out,element);    
        morphologyEx(past,out,CV_MOP_CLOSE,element1);


        vector< vector< Point > >contours;
        findContours(out,contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        vector <Rect> output;
        vector< vector< Point> >::iterator itc= contours.begin();  
        while(itc!=contours.end()){
           
            Rect mr = boundingRect(Mat(*itc));
            rectangle(now,mr,CV_RGB(255,0,0));
            ++itc;
        }






        imshow("capture",now);
        imshow("op",out);
        if (waitKey(10) >=0 )
            break;


        past=now;
    }

    return 0;
}
