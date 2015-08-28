#ifndef VIEWS_MANAGER_H
#define VIEWS_MANAGER_H

#include "cvcommon.h"
#include <map>


/** Manages views from all stages of processing. */
class ViewsManager
{
    std::map<std::string, cv::Mat> _views; 
    ViewsManager ();
    ViewsManager (ViewsManager const&) = delete;
    void operator=(ViewsManager const&) = delete;

public:
    ~ViewsManager ();
    static ViewsManager& getViewsManager();

    /** removes all registrated views */
    void reset();
    /** updates/adds view */
    void update(std::string name, cv::Mat mat);
    /** shows all views */
    void showAll();

};


#endif
