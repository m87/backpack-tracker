#ifndef PEOPLE_DETECTOR_H
#define PEOPLE_DETECTOR_H
#include "cvcommon.h"
#include "Group.h"
#include "Person.h"
#include <vector>
#include "ViewInterface.h"

/** People detection.
 * @see ViewInterface
 */
class PeopleDetector : public ViewInterface
{
    cv::HOGDescriptor hog;
    //area for detection
    const static std::string GROUP_METHOD, ALL_METHOD;

public:
    PeopleDetector ();
    ~PeopleDetector ();

    /** Triggers people detection and filters duplicates */
    void detect(cv::Mat ref);
    /** Get people from extracted groups of potential people*/
    std::vector< std::vector<cv::Rect> > getPeopleFromGroups(cv::Mat ref, std::vector<Group> group);
    /** Get people from whole image */
    std::vector< std::vector<cv::Rect> > getPeopleFromImg(cv::Mat ref);
    /** Check people overlapping
     * @see Person
     * @see ConfigManager::PD_OVERLAP_TRESH
     */
    bool overlaps(Person A, Person B);

};

#endif
