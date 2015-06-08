#include "Blob.h"

long Blob::ID = 1;


Blob::Blob(string name, Mat img, int x, int y, long start, long time){
    _name = name;
    _id = Blob::ID++;
    _img = img;
    _x = x;
    _y = y;
    _start = start;
    _time = time;

}

Blob::~Blob(){

}
