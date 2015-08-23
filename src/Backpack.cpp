#include "Backpack.h"
long Backpack::ID = 0;

Backpack::Backpack(cv::Rect roi, int x, int y){
    MEMORY("Backpack created"); 
    _id = ID++;
    _roi=roi;
    _x = x;
    _y = y;
}


Backpack::~Backpack(){
    MEMORY("Backpack destroyed");

}
