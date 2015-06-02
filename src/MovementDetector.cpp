#include "MovementDetector.h"

MovementDetector::MovementDetector(ConfigManager *config) {
    _step=0;
    _config = config;
    _prep = new Preprocessor(_config->_srcPath,3);
//    _mog2 = new BackgroundSubtractorMOG2(_config->_MOGHistory, _config->_MOGNMixtures, _config->_MOGShadows);
    _mog2 = createBackgroundSubtractorMOG2(_config->_MOGHistory, _config->_MOGNMixtures, _config->_MOGShadows);
   

}

MovementDetector::~MovementDetector() {
//    delete _mog2;
    delete _prep;
    delete _config;
}

Mat MovementDetector::getDebugView(int i) {
    switch(i) {
    case 0:
        return frameNew;
        break;
    case 1:
        return freamReal;
        break;
    case 2:
        return frameNoiseFree;
        break;
    case 3:
        return frameBg;
        break;
    case 4:
        return frameDiff3;
        break;
    case 5:
        Mat out;
    if(_config->_opFrameY>0) {
        resize(freamReal,out,Size(_config->_opFrameX,_config->_opFrameY));
    } else {
        resize(freamReal,out,Size(_config->_opFrameX,_config->_opFrameX/(float)freamReal.cols*freamReal.rows));
    }


        return freamReal;
        break;
    }
    return frameNew;
}

vector<Group> MovementDetector::mog2Filter() {


    _prep->getFrame(frameNew,freamReal,_config->_opFrameX, _config->_opFrameY,  false);
  //  _prep->getFrame(frameBg,_config->_opFrameX, _config->_opFrameY,  false);
    frameNew.copyTo(frameBg);
    cvtColor(frameNew,frameNew,CV_RGB2GRAY);

    _mog2->apply(frameBg,frameDiff) ;
    _mog2->getBackgroundImage(frameBg);

    cvtColor(frameBg,frameBg,CV_RGB2GRAY);

    absdiff(frameBg,frameNew , frameDiff2);

    element = _prep->getStructuringElement(_config->_firstStageDilatation,0);
    bitwise_and(frameDiff,frameDiff2,frameDiff3,Mat());
    threshold(frameDiff3, frameDiff3, _config->_firstStageTreshold, 255,0);
    //absdiff(frameDiff,frameDiff2 , frameDiff3);


    frameDiff.copyTo(frameNoiseFree);
    _prep->saveFrame(frameDiff2);
    dilate(frameDiff3,frameDiff3, element);
    //morphologyEx(frameDiff3, frameDiff3, 1, element);

    vector<Group> output;
    if(_step++==_config->_detectionStep) {
        _step=0;
        findContours( frameDiff3, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)  );

        vector<Rect> boundRect(contours.size());
        vector<vector<Point> > contoursPoly(contours.size());
        Mat drawing;
        frameNew.copyTo(drawing);

        for( unsigned long i = 0; i< contours.size(); i++  )
        {
            approxPolyDP(Mat(contours[i]),contoursPoly[i],10,false);
            boundRect[i] = boundingRect(Mat(contoursPoly[i]));

            vector<Rect> found, found_filtered;
            Mat img1 = frameNew(boundRect[i]);
            Mat img;
            resize(img1,img,Size((img1.cols/(double)img1.rows)*200,200));

            Group group(img1.cols/(double)img.cols, img1.rows/(double)img.rows,boundRect[i].x, boundRect[i].y,img);
            output.push_back(group);
        }
    }



    return output;
}

vector<vector<Point> > MovementDetector::getMovementROIs() {


}
