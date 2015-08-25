#ifndef PEOPLE_DETECTOR_H
#define PEOPLE_DETECTOR_H
#include "cvcommon.h"
#include "Managers.h"
#include "Group.h"
#include "Person.h"
#include <vector>
#include "Utils.h"
#include "ViewInterface.h"

class PeopleDetector : public ViewInterface
{
    cv::HOGDescriptor hog;
    const static std::string GROUP_METHOD, ALL_METHOD;

public:
    PeopleDetector ();
    ~PeopleDetector ();

    std::vector<Person> detect(cv::Mat ref);
    std::vector< std::vector<cv::Rect> > getPeopleFromGroups(cv::Mat ref, std::vector<Group> group);
    std::vector< std::vector<cv::Rect> > getPeopleFromImg(cv::Mat ref);
    void overlayImage(const cv::Mat &background, const cv::Mat &foreground,cv::Mat &output, cv::Point2i location);

};

#endif
