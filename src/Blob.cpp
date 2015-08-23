#include "Blob.h"

long Blob::ID = 1;


Blob::Blob(std::string name, cv::Mat img, int x, int y, int w, int h, long start, long time){
    MEMORY("Blob " + name + " created!");

    _name = name;
    _id = Blob::ID++;
    _img = img;
    _x = x;
    _y = y;
    _w=w;
    _h=h;
    _start = start;
    _time = time;


    SESSION("Blob " + name + " created!");
}

Blob::~Blob(){
    MEMORY("Blob " + _name + " deleted");
}
