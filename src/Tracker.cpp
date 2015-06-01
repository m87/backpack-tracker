#include "Tracker.h"
#include <unistd.h>

int Tracker::maxCorners = 5;
double Tracker::qualityLevel = 0.01;
double Tracker::minDistance = 1;
int Tracker::blockSize = 3;
bool Tracker::useHarrisDetector = false;
double Tracker::k = 0.04;


Tracker::Tracker(){
flag =true;

}

Tracker::~Tracker(){


}
void Tracker::update(vector<Person> people, Mat ref){
   if(people.size() > 0 ){
       if(flag){
     ref.copyTo(_test); 
     ref.copyTo(_ref);
       }
        flag =false;
        for(unsigned long i = 0; i< people.size();i++){
        try{
        Mat mask = Mat::zeros(ref.size(), CV_8UC1);
        mask(people[i].getROI()).setTo(Scalar::all(255));
        vector<Point2f> corners; 
        goodFeaturesToTrack(ref,corners,Tracker::maxCorners,
                Tracker::qualityLevel, Tracker::minDistance, mask);
        if(isTracked(corners)){
            continue;
        }
        people[i].setCorners(corners);
        addPerson(people[i]);

        int rad =2 ;
        /*    for (unsigned long i=0; i< corners.size();i++)
            {
                circle(_test,corners[i],rad,Scalar(255,255,255),-1,8,0);

        }*/
        }catch(Exception e){
            
        }       

    }

}}

void Tracker::addPerson(Person person){
    _people.push_back(person); 
}
bool Tracker::isInside(Point2f point, Rect roi){
    if(point.x > roi.x + roi.width || point.x < roi.x
            || point.y > roi.y + roi.height || point.y <roi.y)
        return false;

    return true;
}
bool Tracker::isTracked(vector<Point2f> corners){
    for(unsigned long i = 0; i < _people.size(); i++){
        if(isInside(corners[i], _people[i].getROI())){
            return true;
        } 
    }
    return false;
}
vector<Person> Tracker::track(Mat ref){
    _ref.copyTo(_ref_prev);
    ref.copyTo(_ref);
    if(_people.size() > 0){
        //cout << _people.size() << endl;
//        #pragma omp parallel for
        for(unsigned long i = 0; i<_people.size();i++){
        try{
       _people[i].setCornersPrev(_people[i].getCorners()); 
        Mat mask = Mat::zeros(ref.size(), CV_8UC1);
        mask(_people[i].getROI()).setTo(Scalar::all(255));
        vector<Point2f> corners; 
      //  goodFeaturesToTrack(ref,corners,Tracker::maxCorners,
       //         Tracker::qualityLevel, Tracker::minDistance, mask);
vector<uchar> _status;
    vector<float> _err;
    
        calcOpticalFlowPyrLK(_ref_prev,_ref,_people[i].getCornersPrev(), corners,_status, _err ) ;
        
        _people[i].setCorners(corners);
        _people[i].updateROI(_status); 
        int rad =2 ;
/*            for (unsigned long i=0; i< corners.size();i++)
            {
                circle(_test,corners[i],rad,Scalar(255,255,255),-1,8,0);

        }*/
        if(_people[i].isOutside(_ref) || !_people[i].isMoveing() || _people[i]._corners_prev.size()==0){
            _people.erase(_people.begin()+i);
        }

       }catch(Exception e){
            
        }       

    }

}

    return _people;
}
void Tracker::print(Mat ref){
    ref.copyTo(_test);
    
    for (unsigned long j=0; j< _people.size();j++)
    {    for (unsigned long i=0; i< _people[j].getCorners().size();i++)
            {
                circle(_test,_people[j].getCorners()[i],2,Scalar(255,255,255),-1,8,0);

        }

//    for (unsigned long j=0; j< _people.size();j++)
    try{  rectangle(_test, _people[j].getROI().tl(), _people[j].getROI().br(), cv::Scalar(0,255,0), 2,8,0);


    }catch(Exception e){
    }
    
    }}

Mat Tracker::getDebugView(int i){
    switch(i){
    case 0: 
    {return _test; break;}
    }
    return _test;

}

