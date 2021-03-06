#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int size) {
//   MEMORY("FrameBuffer created");
    _full=false;
    _loop = 0;
    _size = size;
    for(int i = 0 ; i < _size; i++) {
        _buffer.push_back(cv::Mat());
    }

}

FrameBuffer::FrameBuffer() {
    _full=false;
    _loop=0;

}

FrameBuffer::~FrameBuffer() {
    // MEMORY("FrameBuffer destroyed");
}

cv::Mat FrameBuffer::get(int i) {
    return _buffer[i];
}

cv::Mat FrameBuffer::getLast() {
    if(!_full) return _buffer[0];
    if(_loop == _buffer.size()-1) return _buffer[0];
    return _buffer[_loop+1];
}

cv::Mat FrameBuffer::getFirst() {
    return _buffer[_loop];

}





void FrameBuffer::addFrame(const cv::Mat& mat) {
    mat.copyTo(_buffer[_loop++]);

    if(_loop == _size) {
        _loop = 0;
        _full=true;
    }

}

bool FrameBuffer::isFull() {
    return _full;
}

void FrameBuffer::setSize(int size) {
    _size = size;
    _buffer.clear();
    for(int i = 0 ; i < _size; i++) {
        _buffer.push_back(cv::Mat());
    }
}

