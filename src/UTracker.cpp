#include "UTracker.h"

UTracker::UTracker(){
kk=0;
}
UTracker::~UTracker(){

}
bool UTracker::chechkOverlapping(Person p){
        for(unsigned long i=0; i< _people.size();i++){
            if(p.getID() == _people[i].getID()) continue;
          if(p.ROIOverlapping(_people[i]._roid))
              return true;
        }
 return false;
}

void UTracker::addPeople(vector<Person> people, Mat ref){
    for(unsigned long p = 0; p< people.size();p++){
 //       if(chechkOverlapping(people[p])) continue;

       _people.push_back(people[p]);
        Ptr<Tracker> t = Tracker::create("MIL");
        t->init(ref,people[p]._roid);
        _trackers.push_back(t);



    }
    
}

double UTracker::fillLevel(Mat bg, Mat ref, Person p ){
    double out = 0.0;
    double b=0.0;
    Rect roi =  p.getROI();
    b=roi.width*roi.height;
    Mat diff;
 try{
    absdiff(bg(roi),ref(roi),diff);
 }catch(Exception e){
     return 0.0;
 }
    threshold(diff,diff,2,255,0);
    out = countNonZero(diff)/b;
    return out;
}


void UTracker::update(Mat ref, Mat bg){
    if(kk++ == 5){
    kk=0;
    //#pragma omp parallel for 
 /*    
    for (unsigned long j=0; j< _people.size();j++)
    { if(chechkOverlapping(_people[j])
       || fillLevel(bg,ref,_people[j]) < 0.3
            ){
           _people.erase(_people.begin()+j); 
           _trackers.erase(_trackers.begin()+j); 
    }
    }*/
    #pragma omp parallel for 
    for (unsigned long j=0; j< _people.size();j++)
    {
     //  }else{
        _trackers[j]->update(ref, _people[j]._roid);

    


}}}//}

Mat UTracker::getDebugView(Mat ref){
    Mat out;
    ref.copyTo(out);
    
    for (unsigned long j=0; j< _people.size();j++)
    try{  rectangle(out, _people[j]._roid.tl(), _people[j]._roid.br(), cv::Scalar(0,255,0), 2,8,0);


    }catch(Exception e){
    }
    
return out;
   
}
