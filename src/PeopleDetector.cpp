#include "PeopleDetector.h"

const std::string PeopleDetector::GROUP_METHOD = "group";
const std::string PeopleDetector::ALL_METHOD = "all";

PeopleDetector::PeopleDetector(){
    MEMORY("PeopleDetector created");

    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

PeopleDetector::~PeopleDetector(){
    MEMORY("PeopleDetector destroyed");

}


void PeopleDetector::detect(cv::Mat ref){
    std::vector<std::vector<cv::Rect> > rects; 
    std::string method = ConfigManager::getConfigManager().get<std::string>(ConfigManager::PD_METHOD);

    if(method == GROUP_METHOD){
        rects = getPeopleFromGroups(ref,DataManager::getDataManager().getGroups());
    }
    if(method == ALL_METHOD){
        rects = getPeopleFromImg(ref);
    }


    for(unsigned long i=0;i<rects.size();i++){
        for(unsigned long j=0; j<rects[i].size();j++ ){
            Person person(rects[i][j]);
            DataManager::getDataManager().people.insert(std::pair<int, Person>(person.getID(),person));
            //distinct
        }
    }

}





std::vector<std::vector<Rect> > PeopleDetector::getPeopleFromGroups(cv::Mat ref, std::vector<Group> group){
    std::vector< std::vector<Rect> > output;
    cv::Mat view;
    ref.copyTo(view);
for( unsigned long i = 0; i< group.size(); i++  )
        {
            std::vector<Rect> found, found_filtered;
            hog.detectMultiScale(group[i].getImg(), found, 0, Size(8,8), Size(32,32), 1.05, 2);

                        size_t ii, j;
            for (ii=0; ii<found.size(); ii++)
            {
                Rect r = found[ii];
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
        if(found_filtered.size() > 0){
                group.erase(group.begin()+i);
            }

        }


    display(ConfigManager::VIEW_PD_RESULT, view);

return output;

}


std::vector<std::vector<Rect> > PeopleDetector::getPeopleFromImg(cv::Mat ref){
    std::vector< std::vector<Rect> > output;
    cv::Mat view;
    ref.copyTo(view);
            std::vector<Rect> found, found_filtered;
            hog.detectMultiScale(ref, found, 0, Size(8,8), Size(32,32), 1.05, 2);

                        size_t ii, j;
            for (ii=0; ii<found.size(); ii++)
            {
                Rect r = found[ii];
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

