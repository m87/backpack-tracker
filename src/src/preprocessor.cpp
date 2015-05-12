#include "preprocessor.h"

Preprocessor::Preprocessor(string file) {
    _cap = new VideoCapture(file);
    //cap.open(file);
    _frameBufferSize = 0;
    _currentFrameBufferPos = 0;

    if(!_cap->isOpened())
        throw GenericException(GenericException::CAP_NOT_OPENED);


}

Preprocessor::Preprocessor(string file, unsigned long n) {
    _cap = new VideoCapture(file);
    //cap.open(file);
    _frameBufferSize = n;
    _currentFrameBufferPos = 0;

    if(!_cap->isOpened())
        throw GenericException(GenericException::CAP_NOT_OPENED);


}
Preprocessor::~Preprocessor() {
    delete _cap;
}

unsigned long Preprocessor::getFrameBufferSize() {
    return _frameBufferSize;
}

unsigned long Preprocessor::getCurrentFrameBufferSize() {
    return _frameBuffer.size();
}

Mat Preprocessor::getFrameFromBuffer(unsigned long n) {
    if(n >= _frameBuffer.size())
        throw GenericException(GenericException::INDEX_OUT_OF_FRAME_BUFFER);
    return _frameBuffer[n];
}

void Preprocessor::saveFrame(Mat frame) {
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
    Mat tmp;
    for(unsigned long i=0; i<n; i++) *_cap >> tmp;
}

void Preprocessor::getFrame(Mat &out,Mat &out_real,float w , float h, bool gray) {
    Mat tmp;
    *_cap >> tmp;
    tmp.copyTo(out_real);
    if(h>0) {
        resize(tmp,out,Size(w,h));
    } else {
        resize(tmp,out,Size(w,w/(float)tmp.cols*tmp.rows));
    }

    if(gray) {
        cvtColor(out,out,CV_RGB2GRAY);
    }

}

void Preprocessor::getAvgFrame(Mat &output){
    if(_frameBuffer.size()== _frameBufferSize){
        for(unsigned long i=0; i<_frameBufferSize;i++){
            output+=_frameBuffer[i];
        }    
        output = output / _frameBufferSize;
    }
    
    

}

Mat Preprocessor::getStructuringElement(int size, int type){
  return cv::getStructuringElement( type, Size( 2*size + 1, 2*size+1  ), Point( size, size  )  );

}

void Preprocessor::getFrame(Mat &out,float w , float h, bool gray) {
    Mat tmp;
    *_cap >> tmp;
    if(h>0) {
        resize(tmp,out,Size(w,h));
    } else {
        resize(tmp,out,Size(w,w/(float)tmp.cols*tmp.rows));
    }

    if(gray) {
        cvtColor(out,out,CV_RGB2GRAY);
    }

}
