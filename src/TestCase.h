#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>
#include "cvcommon.h"
#include "Utils.h"

/* Test case class
 * @see Benchmark
 */
class TestCase
{
public:
    ///Test case types
    static const std::string BACKPACK, PERSON, NO_BACKPACK, NO_PERSON;
    TestCase (std::string name, std::string type, int x, int y, int width, int height, int time);
    ~TestCase ();
    std::string _name;
    std::string _type;
    ///?
    std::string _action;
    ///start time
    int _time;
    ///region to check
    cv::Rect _roi;

};

#endif
