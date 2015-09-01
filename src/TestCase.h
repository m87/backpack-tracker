#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>
#include "cvcommon.h"


class TestCase
{

public:
    static const std::string BACKPACK, PERSON;
    std::string _name;
    string _type;
    int _time;
    cv::Rect _roi;
    TestCase (std::string name, std::string type, int x, int y, int width, int height, int time);
    ~TestCase ();

};

#endif
