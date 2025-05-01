#ifndef MISC_H
#define MISC_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

namespace misc
{
    class misc
    {
        public:
        template <class T>
        std::string convertToString(const T &t)
        {
            std::ostringstream s;
            s << t;
            return s.str();
        }
    };
}

#endif //MISC_H