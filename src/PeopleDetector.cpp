#include "PeopleDetector.h"
//find groups of potential people 
const std::string PeopleDetector::GROUP_METHOD = "group";
//use whole frame
const std::string PeopleDetector::ALL_METHOD = "all";

PeopleDetector::PeopleDetector() {
 //   MEMORY("PeopleDetector created");
    //init hog detecor
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

PeopleDetector::~PeopleDetector() {
   // MEMORY("PeopleDetector destroyed");

}

bool PeopleDetector::overlaps(Person A, Person B) {
    cv::Rect2d inter = A._roid & B._roid;
    if(inter.width > A._roid.width * ConfigManager::getConfigManager().get<double>(ConfigManager::PD_OVERLAP_TRESH)  || inter.height > A._roid.height * ConfigManager::getConfigManager().get<double>(ConfigManager::PD_OVERLAP_TRESH))
    {
        return true;

    }
    return false;


}

void PeopleDetector::detect(cv::Mat ref) {
    std::vector<std::vector<cv::Rect> > rects;
    std::string method = ConfigManager::getConfigManager().get<std::string>(ConfigManager::PD_METHOD);

    if(method == GROUP_METHOD) {
        rects = getPeopleFromGroups(ref,DataManager::getDataManager().getGroups());
    }
    if(method == ALL_METHOD) {
        rects = getPeopleFromImg(ref);
    }


    for(unsigned long i=0; i<rects.size(); i++) {
        for(unsigned long j=0; j<rects[i].size(); j++ ) {
            Person person(rects[i][j]);
            bool ok=true;
            for(auto p = DataManager::getDataManager().people.begin(); p != DataManager::getDataManager().people.end();p++){
                if(overlaps(person, p->second)) {
                    ok=false;
                    break;
                }
                }
            if(ok) {
                DataManager::getDataManager().people.insert(std::pair<int, Person>(person.getID(),person));
                DataManager &dm = DataManager::getDataManager();
                dm.avgH = dm.n*dm.avgH;
                dm.avgW = dm.n*dm.avgW;
                dm.n++;
                dm.avgH += person._roid.height;
                dm.avgW += person._roid.width;
                dm.avgH /= dm.n;
                dm.avgW /= dm.n;
            }
        }
    }

}





std::vector<std::vector<cv::Rect> > PeopleDetector::getPeopleFromGroups(cv::Mat ref, std::vector<Group> group) {
    std::vector< std::vector<cv::Rect> > output;
    cv::Mat view;
    ref.copyTo(view);
    for( unsigned long i = 0; i< group.size(); i++  )
    {
        std::vector<cv::Rect> found, found_filtered;
        hog.detectMultiScale(group[i].getImg(), found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);

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
        for (ii=0; ii<found_filtered.size(); ii++)
        {

            found_filtered[ii].width = found_filtered[ii].width * group[i].getWidthScale();
            found_filtered[ii].height = found_filtered[ii].height * group[i].getHeightScale();
            found_filtered[ii].x = group[i].getRelativeX() + found_filtered[ii].x*group[i].getWidthScale();
            found_filtered[ii].y = group[i].getRelativeY() + found_filtered[ii].y*group[i].getHeightScale();

            found_filtered[ii].x += cvRound(found_filtered[ii].width*0.1);
            found_filtered[ii].width = cvRound(found_filtered[ii].width*0.8);
            found_filtered[ii].y += cvRound(found_filtered[ii].height*0.06);
            found_filtered[ii].height = cvRound(found_filtered[ii].height*0.9);
            rectangle(view, found_filtered[ii].tl(), found_filtered[ii].br(), cv::Scalar(0,255,0), 2,8,0);


        }
        output.push_back(found_filtered);
        if(found_filtered.size() > 0) {
            group.erase(group.begin()+i);
        }

    }


    display(ConfigManager::VIEW_PD_RESULT, view);

    return output;

}


std::vector<std::vector<cv::Rect> > PeopleDetector::getPeopleFromImg(cv::Mat ref) {
    std::vector< std::vector<cv::Rect> > output;
    cv::Mat view;
    ref.copyTo(view);
    std::vector<cv::Rect> found, found_filtered;
    hog.detectMultiScale(ref, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);

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
    for (ii=0; ii<found_filtered.size(); ii++)
    {

        found_filtered[ii].x += cvRound(found_filtered[ii].width*0.1);
        found_filtered[ii].width = cvRound(found_filtered[ii].width*0.8);
        found_filtered[ii].y += cvRound(found_filtered[ii].height*0.06);
        found_filtered[ii].height = cvRound(found_filtered[ii].height*0.9);
        rectangle(view, found_filtered[ii].tl(), found_filtered[ii].br(), cv::Scalar(0,255,0), 2,8,0);


    }
    output.push_back(found_filtered);



    display(ConfigManager::VIEW_PD_RESULT, view);

    return output;

}

