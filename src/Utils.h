
#ifndef UTILS_H
#define UTILS_H 

#include <iostream>
#include <string>
#include <sstream>

#define INFO(msg) (std::cout << "\x1b[32;1m" << "[Info] "  << "\x1b[0m"  << msg << std::endl)
#define ERROR(msg) (std::cout << "\x1b[31;1m" << "[Error] "  << "\x1b[0m"  << msg << std::endl)
#define WARNING(msg) (std::cout << "\x1b[34;1m" << "[Warning] "  << "\x1b[0m"  << msg << std::endl)
#define SESSION(msg) (std::cout << "\x1b[33;1m" << "[Session] "  << "\x1b[0m"  << msg << std::endl)
#define MEMORY(msg) (std::cout << "\x1b[35;1m" << "[Memory] "  << "\x1b[0m"  << msg << std::endl)
#define VERBOSE(msg) (std::cout << "\x1b[36;1m" << "[Verbose] "  << "\x1b[0m"  << msg << std::endl)
#define VERBOSE_O(msg) //(std::cout << "\x1b[37;1m" << "[!Verbose!] "  << "\x1b[0m"  << msg << std::endl)

namespace utils {
    namespace str{
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
