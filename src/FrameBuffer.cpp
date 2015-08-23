#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int size){
    MEMORY("FrameBuffer created");
    full=false;    
    _loop = 0;
    _size = size;
    for(int i = 0 ; i < _size; i++){
        _buffer.push_back(cv::Mat());
    } 

}


FrameBuffer::~FrameBuffer(){
    MEMORY("FrameBuffer destroyed");
}


void FrameBuffer::addFrame(const cv::Mat& mat){
    mat.copyTo(_buffer[_loop++]);

    if(_loop == _size){
        _loop = 0;
        full=true;
    }

}

bool FrameBuffer::isFull(){
    return full;
}

void FrameBuffer::setSize(int size){
    _size = size;
    _buffer.clear();
    for(int i = 0 ; i < _size; i++){
        _buffer.push_back(cv::Mat());
    }
}

int FrameBuffer::checkPixel(int x, int y, int value, int tresh){
    int sum = 0;
    if(!full) return sum; 
    for(int i =0 ;i < _size; i++){
        if(value>=0){
            if(_buffer[i].at<int>(y,x) == value ) sum++;            
        }else{

        }
    }
    return sum;
}


void FrameBuffer::mask(cv::Mat in, cv::Mat& input, int tresh){
    in.copyTo(input);
    if(!full) return;
    for(int i =0 ;i < _size; i++){
        bitwise_and(input,_buffer[i],input);

    }
}
