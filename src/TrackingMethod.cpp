#include "TrackingMethod.h"

TrackingMethod::TrackingMethod(){
        hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

bool TrackingMethod::recheckTracker(cv::Mat ref){
    cv::Mat tmp;
    ref.copyTo(tmp);
            cv::resize(tmp,tmp,cv::Size((tmp.cols/(double)tmp.rows)*ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_SIZE_FIX),ConfigManager::getConfigManager().get<int>(ConfigManager::TRACKING_SIZE_FIX)));
    std::vector<cv::Rect>  found, found_filtered;
    hog.detectMultiScale(tmp, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);
     size_t ii, j;
        for (ii=0; ii<found.size(); ii++)
        {
            cv::Rect r = found[ii];
            for (j=0; j<found.size(); j++)
                if (j!=ii && (r & found[j])==r)
                    break;
            if (j==found.size())
                found_filtered.push_back(r);

        }
        if(found_filtered.size()){

            for(unsigned long k = 0; k< found_filtered.size();k++){
if( found_filtered[k].width >= ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_STATIC_TRESH) * tmp.cols && found_filtered[k].height >= ConfigManager::getConfigManager().get<double>(ConfigManager::TRACKING_STATIC_TRESH) * tmp.rows){
            return true;
       

            }

                }}else{
            return false;
        }
                    
    return false;

}


