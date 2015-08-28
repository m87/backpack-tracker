#include "Backpack.h"
long Backpack::ID = 0;

Backpack::Backpack(cv::Rect roi, cv::Mat img, cv::Mat base) {
    // MEMORY("Backpack created");
    _id = ID++;
    _roi=roi;
    img.copyTo(_img);
    base.copyTo(_base);
    _confidence = 0;
    _checks = 0;
    _stable = 0;
    _stableConfidance = 0;
    isbase = true;
    saved=false;
}


Backpack::~Backpack() {
    //MEMORY("Backpack destroyed");

}

void Backpack::setNewBase(cv::Mat base) {
    if(isbase) {
        base.copyTo(_base);
        base = false;
    }
}

void Backpack::incStableConfidance(int i) {
    if(_stableConfidance<=255) {
        _stableConfidance+=i;

    }
}

cv::Scalar Backpack::getColor(){
   return cv::Scalar(255-_stableConfidance,_stableConfidance,0); 
}

bool Backpack::checkOverlapping(cv::Rect A, cv::Rect B) {
    cv::Rect inter = A & B;
    if(inter.width > A.width * 0.2  || inter.height > A.height * 0.2)
    {
        return true;

    }
    return false;

}

void Backpack::takeSnapshot(int size, std::map<int, Person> people) {
    cv::Rect rect = _roi; 
    rect.x-=size;
    rect.y-=size;
    rect.width+=size;
    rect.height+=size;
    
    for(auto t=people.begin(); t!=people.end(); t++){
        if(checkOverlapping(t->second.getROI(),rect)){
            _people.push_back(t->first);
        }
    }



}

void Backpack::incConfidence(int i) {
    _confidence+=i;
}

int Backpack::getConfidence() {
    return _confidence;
}

cv::Mat Backpack::getImg() {
    return _img;
}

cv::Mat Backpack::getBase() {
    return _base;
}

long Backpack::getID() {
    return _id;
}

cv::Rect Backpack::getRoi() {
    return _roi;
}

void Backpack::incChecks(int i) {
    _checks+=i;
}

int Backpack::getChecks() {
    return _checks;
}


void Backpack::shrink(cv::Mat sum) {
    try {
        cv::Mat tmp = sum(_roi);
        std::vector<cv::Vec4i> hierarchy;
        std::vector<std::vector<cv::Point> > contours;
        findContours(tmp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0)  );
        std::vector<cv::Rect> boundRect(contours.size());
        std::vector<std::vector<cv::Point> > contoursPoly(contours.size());

        approxPolyDP(cv::Mat(contours[0]),contoursPoly[0],10,false);
        boundRect[0] = boundingRect(cv::Mat(contoursPoly[0]));

        _roi = boundRect[0];

    } catch(cv::Exception e) {}
}
