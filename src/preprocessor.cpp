#include "preprocessor.h"

Preprocessor::Preprocessor(string file){
cap = new VideoCapture(file);

if(!cap->isOpened())
    throw Exception();


}

Preprocessor::~Preprocessor(){
delete cap;
}

void Preprocessor::getFrame(Mat &out){
     *cap >> out;

}

