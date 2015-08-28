#ifndef MD_METHOD_H
#define MD_METHOD_H
#include "cvcommon.h"
#include "Group.h"
#include <vector>


/** Movement detection method abstract class */

class MDMethod
{

public:
    virtual void detect(const cv::Mat& src)=0;
    virtual void initMethod(ConfigManager& config)=0;
    virtual std::vector< std::vector<cv::Point> > getROIs()=0;

};



#endif
