#include "TestCase.h"
const std::string TestCase::PERSON = "person";
const std::string TestCase::BACKPACK = "backpack";

TestCase::TestCase(std::string name, std::string type, int x, int y, int width, int height, int time){

    MEMORY("TestCase created");
    _name = name;
    _type = type;
    _roi.x= x ;
    _roi.y=y;
    _roi.width = width;
    _roi.height = height;
    _time = time;
}


TestCase::~TestCase(){
    MEMORY("TestCase destroyed");
}
