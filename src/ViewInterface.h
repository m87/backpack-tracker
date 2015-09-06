#ifndef VIEW_INTERFACE_H
#define VIEW_INTERFACE_H
#include "cvcommon.h"
#include "ViewsManager.h"
#include "ConfigManager.h"


/** wrapper for update method
 * @see ViewsManager
 */
class ViewInterface
{

public:
    /** updates view if required */
    void display(std::string name, cv::Mat mat){ 
        if(ConfigManager::getConfigManager().get<bool>(name)){
            ViewsManager::getViewsManager().update(name, mat);
        }
    }
};

#endif
