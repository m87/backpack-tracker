#include "Preprocessor.h"
Preprocessor::Preprocessor(std::string file) : _cap(new cv::VideoCapture(file)) {
    MEMORY("Preprocessor created");

    _frameBufferSize = 0;
    _currentFrameBufferPos = 0;

    if(!_cap->isOpened())
        throw GenericException(GenericException::CAP_NOT_OPENED);

    SESSION("Preprocessor created");
}

Preprocessor::Preprocessor(std::string file, unsigned long n) : _cap(new cv::VideoCapture(file))  {
    MEMORY("Preprocessor created");

    _frameBufferSize = n;
    _currentFrameBufferPos = 0;

    if(!_cap->isOpened())
        throw GenericException(GenericException::CAP_NOT_OPENED);


    SESSION("Preprocessor created");
}
Preprocessor::~Preprocessor() {
    SESSION("Preprocessor deleted");
    MEMORY("Preprocessor deleted");
}



void Preprocessor::printParams(cv::Algorithm a) {
    vector<std::string> params;

    for(unsigned long i=0; i<params.size(); i++)
        INFO("Preprocessor: Params: " + params[i]);
}
unsigned long Preprocessor::getFrameBufferSize() {
    return _frameBufferSize;
}

unsigned long Preprocessor::getCurrentFrameBufferSize() {
    return _frameBuffer.size();
}

cv::Mat Preprocessor::getFrameFromBuffer(unsigned long n) {
    if(n >= _frameBuffer.size())
        throw GenericException(GenericException::INDEX_OUT_OF_FRAME_BUFFER);
    return _frameBuffer[n];
}

void Preprocessor::saveFrame(cv::Mat frame) {
    if(_frameBuffer.size()< _frameBufferSize) {
        _frameBuffer.push_back(frame);
    } else {

        _currentFrameBufferPos = _currentFrameBufferPos < _frameBufferSize-1 ? _currentFrameBufferPos+1 : 0;


        _frameBuffer[_frameBufferSize-1-(_currentFrameBufferPos)] = frame;

    }

}

void Preprocessor::clearFrameBuffer() {
    _frameBuffer.clear();
    _currentFrameBufferPos = 0;
    _frameBufferSize = 0;
}


void Preprocessor::skipNFrames(unsigned long n) {
    cv::Mat tmp;
    for(unsigned long i=0; i<n; i++) *_cap >> tmp;
}

void Preprocessor::getFrame(cv::Mat &out,cv::Mat &out_real,float w , float h, bool gray) {
    cv::Mat tmp;
    *_cap >> tmp;
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
}

void Preprocessor::getSumFrame(cv::Mat &output) {

    if(_frameBuffer.size()== _frameBufferSize) {
        for(unsigned long i=0; i<_frameBufferSize; i++) {
            output+=_frameBuffer[i];
        }
    }



}
void Preprocessor::getAvgFrame(cv::Mat &output) {
    if(_frameBuffer.size()== _frameBufferSize) {
        for(unsigned long i=0; i<_frameBufferSize; i++) {
            output+=_frameBuffer[i];
        }
        output = output / _frameBufferSize;
    }



}

cv::Mat Preprocessor::getStructuringElement(int size, int type) {
    return cv::getStructuringElement( type, cv::Size( 2*size + 1, 2*size+1  ), cv::Point( size, size  )  );

}

void Preprocessor::getFrame(cv::Mat &out,float w , float h, bool gray) {
    cv::Mat tmp;
    *_cap >> tmp;
    if(h>0) {
        resize(tmp,out,cv::Size(w,h));
    } else {
        resize(tmp,out,cv::Size(w,w/(float)tmp.cols*tmp.rows));
    }

    if(gray) {
        cvtColor(out,out,CV_RGB2GRAY);
    }

}
