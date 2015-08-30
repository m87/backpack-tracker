#include "UI.h"

cv::Mat UI::FINAL, UI::FINAL_CP;
int UI::pirintID;



UI::UI() {
    MEMORY("UI created");
}

UI::~UI() {
    MEMORY("UI destroyed");
}

void UI::callbackMouse(int event, int x ,int y , int flags, void* userdata) {

    if  ( event == EVENT_LBUTTONDOWN  )
    {
        for(unsigned long t = 0; t <  DataManager::getDataManager().backpacks.size(); t++) {
            if( x > DataManager::getDataManager().backpacks[t].getRoi().x &&
                    y > DataManager::getDataManager().backpacks[t].getRoi().y &&
                    x < DataManager::getDataManager().backpacks[t].getRoi().x +DataManager::getDataManager().backpacks[t].getRoi().width &&
                    x < DataManager::getDataManager().backpacks[t].getRoi().x  + DataManager::getDataManager().backpacks[t].getRoi().height

              ) {
                UI::pirintID = t;
                INFO("Backpack ["+utils::str::to_string<double>(DataManager::getDataManager().backpacks[t]._stableConfidance/254.0*100)+"%]: "+utils::str::to_string<int>(DataManager::getDataManager().backpacks[t].getID()));
                break;
            }
        }

    }
    if  ( event == EVENT_RBUTTONDOWN  )
    {
        UI::pirintID = -1;
        return;
    }
}
