#include "Backpack.h"
long Backpack::ID = 0;
cv::Mat Backpack::PATCH;

Backpack::Backpack(cv::Rect roi, cv::Mat img, cv::Mat base, cv::Mat patch, int life, int countDown) {
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
    destoyed = false;
    this->life= life; 
    this->countDown = countDown;
    wasStable = false;
    patch.copyTo(patchBase);
}

Backpack::Backpack(){

}


void Backpack::overlayImage(const cv::Mat &background, const cv::Mat &foreground,
cv::Mat &output, cv::Point2i location)
{
background.copyTo(output);


for(int y = std::max(location.y , 0); y < background.rows; ++y)
{
int fY = y - location.y; // because of the translation

if(fY >= foreground.rows)
break;

for(int x = std::max(location.x, 0); x < background.cols; ++x)
{
int fX = x - location.x; // because of the translation.

if(fX >= foreground.cols)
break;

double opacity =
((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

/ 255.;



for(int c = 0; opacity > 0 && c < output.channels(); ++c)
{
unsigned char foregroundPx =
  foreground.data[fY * foreground.step + fX * foreground.channels() + c];
unsigned char backgroundPx =
  background.data[y * background.step + x * background.channels() + c];
output.data[y*output.step + output.channels()*x + c] =
  backgroundPx * (1.-opacity) + foregroundPx * opacity;

}

}

}

}

void Backpack::status(){
    if(countDown--<=0){
        SESSION("Backpack ID: " + utils::str::to_string<int>(_id)+ " ALERT, calling security") ;
    }
}

void Backpack::patch(cv::Mat &dst){
    if(destoyed && life >0 ){
            long x = _roi.x+_roi.width;
            long y = _roi.y+_roi.height;
            //overlayImage(dst.rowRange(_roi.y,y).colRange(_roi.x,x),im,im2, cv::Point(0,0));
            //overlayImage(dst.rowRange(10,200).colRange(10,200),im,im2, cv::Point(0,0));
            //im2.copyTo(dst.rowRange(_roi.y,y).colRange(_roi.x,x));
            patchBase.copyTo(dst.rowRange(_roi.y,y).colRange(_roi.x,x));
            if(_id==67)
            life--;
         
    }
}

Backpack::~Backpack() {
    //MEMORY("Backpack destroyed");

}

void Backpack::setNewBase(cv::Mat base) {
    //if(isbase) {
        base.copyTo(_base);
        isbase = false;
    //}
}

void Backpack::incStableConfidance(int i) {
    if(_stableConfidance<=255) {
        _stableConfidance+=i;

    }
}

cv::Scalar Backpack::getColor(){
   return cv::Scalar(0,_stableConfidance,255-_stableConfidance); 
}

bool Backpack::checkOverlapping(cv::Rect A, cv::Rect B, double treshold) {
    cv::Rect inter = A & B;
    if(inter.width > B.width * treshold  || inter.height > B.height * treshold)
    {
        return true;

    }
    return false;

}

void Backpack::takeSnapshot(int size, std::map<int, Person> people, double treshold, cv::Mat ref, std::string pathRuntime) {
    if(saved) return;
    cv::Rect rect = _roi; 
    rect.x-=size;
    rect.y-=size;
    rect.width+=size;
    rect.height+=size;

    cv::imwrite(pathRuntime+"/"+utils::str::to_string<int>(_id)+".png", ref(_roi));
    
    for(auto t=people.begin(); t!=people.end(); t++){
        if(checkOverlapping(rect,t->second.getROI(),treshold)){
            _people.push_back(t->first);

            cv::imwrite(pathRuntime+"/"+utils::str::to_string<int>(_id)+"-"+utils::str::to_string<int>(t->second.getID())+".png", ref(t->second._roid));
        }
    }
    

    saved=true;


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
