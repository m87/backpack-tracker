#include "PeopleDetector.h"

PeopleDetector::PeopleDetector(){

    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

PeopleDetector::~PeopleDetector(){


}

Mat PeopleDetector::getDebugView(int i){
    switch(i){
        case 0: 
            return drawing; break;

    }
    return drawing;
}

vector<Person> PeopleDetector::getPeople(Mat ref, vector<Group> group){
    vector<Person> output;
    vector<vector<Rect> > rects = getPeopleROIs(ref,group);
    for(unsigned long i=0;i<rects.size();i++){
        for(unsigned long j=0; j<rects[i].size();j++ ){
            Person person(rects[i][j]);
            output.push_back(person);
        }
    }

    return output;
}

vector<vector<Rect> > PeopleDetector::getPeopleROIs(Mat ref, vector<Group> group){
    vector< vector<Rect> > output;
    ref.copyTo(drawing);
for( unsigned long i = 0; i< group.size(); i++  )
        {
            vector<Rect> found, found_filtered;
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
                rectangle(drawing, found_filtered[ii].tl(), found_filtered[ii].br(), cv::Scalar(0,255,0), 2,8,0);

            }
            output.push_back(found_filtered);
        }

return output;

}


