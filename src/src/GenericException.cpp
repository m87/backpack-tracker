#include "GenericException.h"

const string GenericException::CAP_NOT_OPENED = "Capture is not opened";
const string GenericException::INDEX_OUT_OF_FRAME_BUFFER = "Index out of frameBuffer";

const char* GenericException::what() const throw()
    {
        return msg.c_str();
    }


