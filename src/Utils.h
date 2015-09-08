
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/core.hpp>

#define INFO(msg) (std::cout << "\x1b[32;1m" << "[Info] "  << "\x1b[0m"  << msg << std::endl)
#define ERROR(msg) (std::cout << "\x1b[31;1m" << "[Error] "  << "\x1b[0m"  << msg << std::endl)
#define WARNING(msg) (std::cout << "\x1b[34;1m" << "[Warning] "  << "\x1b[0m"  << msg << std::endl)
#define SESSION(msg) (std::cout << "\x1b[33;1m" << "[Session] "  << "\x1b[0m"  << msg << std::endl)
#define MEMORY(msg) (std::cout << "\x1b[35;1m" << "[Memory] "  << "\x1b[0m"  << msg << std::endl)
#define VERBOSE(msg) (std::cout << "\x1b[36;1m" << "[Verbose] "  << "\x1b[0m"  << msg << std::endl)
#define VERBOSE_O(msg) //(std::cout << "\x1b[37;1m" << "[!Verbose!] "  << "\x1b[0m"  << msg << std::endl)



#define _TRACKER_REMOVED -2
#define _NO_PRINT -1

namespace utils {

namespace detect {
template < typename T >
bool checkOverlapping(cv::Rect_<T> A, cv::Rect_<T> B, double treshold) {
    cv::Rect_<T> inter = A & B;
    if(inter.width > B.width * treshold  || inter.height > B.height * treshold)
    {
        return true;

    }
    return false;



}
/**check overlaping of 2 rectangles
 * @param treshold factor of overlaping
 * @param flag if true, returns false 
 */
template < typename T >
bool checkOverlapping(cv::Rect_<T> A, cv::Rect_<T> B, double treshold, bool flag) {
    if(flag) return false;
    else{
        return checkOverlapping(A,B,treshold);
    }



}

}



namespace str {
    ///conver to string
template < typename T >
std::string to_string( const T& n  )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;

}
}

}
#endif
