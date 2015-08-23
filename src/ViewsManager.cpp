#include "ViewsManager.h"

ViewsManager::ViewsManager(){
    MEMORY("ViewsManager created");
}

ViewsManager::~ViewsManager(){
    MEMORY("ViewsManager deleted");

}

ViewsManager& ViewsManager::getViewsManager(){
    VERBOSE_O("ViewsManager: instance request");
    static ViewsManager instance;
    return instance;
                    
}


void ViewsManager::update(std::string name, cv::Mat mat){
    _views[name] = mat;
    
    VERBOSE_O("ViewsManager: view " + name + " updated");
}

void ViewsManager::showAll(){
    for(auto p : _views){
        imshow(p.first, p.second);
    }

}


void ViewsManager::reset(){
    _views.clear();


    VERBOSE("ViewsManager: views cleared");
}
