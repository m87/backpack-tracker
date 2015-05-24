#ifndef GENERIC_EXCEPTION_H
#define GENERIC_EXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class GenericException : public exception
{
    /* data */
    string msg;

public:
    static const string CAP_NOT_OPENED;
    static const string INDEX_OUT_OF_FRAME_BUFFER;
    

    GenericException(string m = "something gone wrong"):msg(m) {}
    ~GenericException() throw() {}
    virtual const char* what() const throw();

};


#endif
