#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include "windows.h"
#include "misc.h"

namespace timestamp
{
    class timestamp
    {
        public:
        std::string getDateAndTime(void)
        {
            SYSTEMTIME t;
            #if defined USE_SYSTEM_TIME
             GetSystemTime(&t);
            #else
             GetLocalTime(&t);
            #endif
            std::string s = misc::misc().convertToString(t.wDay) + "-" + 
                            misc::misc().convertToString(t.wMonth) + "-" +
                            misc::misc().convertToString(t.wYear) + "_" +  
                            misc::misc().convertToString(t.wHour) + "-" + 
                            misc::misc().convertToString(t.wMinute);                          
            return s;
        }
    };
}
#endif //TIMESTAMP_H

