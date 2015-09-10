#include "Preprocessor.h"
Preprocessor::Preprocessor(std::string file) : _cap(new cv::VideoCapture(file)) {
    MEMORY("Preprocessor created");

    if(!_cap->isOpened())
        throw GenericException(GenericException::CAP_NOT_OPENED);

}

Preprocessor::~Preprocessor() {
    MEMORY("Preprocessor deleted");
}

bool Preprocessor::getFrame(cv::Mat &out,cv::Mat &out_real,float w , float h, bool gray) {
    cv::Mat tmp;
    *_cap >> tmp;
    if(tmp.rows ==0) return false;
    tmp.copyTo(out_real);
    if(h>0) {
        resize(tmp,out,cv::Size(w,h));
    } else {
        resize(tmp,out,cv::Size(w,w/(float)tmp.cols*tmp.rows));
    }

    if(gray) {
        cvtColor(out,out,CV_RGB2GRAY);
    }


    display(ConfigManager::VIEW_FRAME_REAL, out_real);
    display(ConfigManager::VIEW_FRAME_RESIZED, out);
    VERBOSE_O("Preprocesso:: resized frame reuqest");
    return true;
}

bool Preprocessor::getFrame(cv::Mat &out,float w , float h, bool gray) {
    cv::Mat tmp;
    *_cap >> tmp;
    if(tmp.rows ==0) return false;
    if(h>0) {
        resize(tmp,out,cv::Size(w,h));
    } else {
        resize(tmp,out,cv::Size(w,w/(float)tmp.cols*tmp.rows));
    }

    if(gray) {
        cvtColor(out,out,CV_RGB2GRAY);
    }
    return true;

}
