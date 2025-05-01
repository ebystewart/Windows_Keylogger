#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <sstream>
#include <fstream>
#include "windows.h"
#include "Timestamp.h"

namespace fileOperations
{
    class fileOps
    {
        public:
        std::string getCurrentDirectory(void)
        {
            char path[MAX_PATH];
            DWORD ret = GetCurrentDirectory(MAX_PATH, (LPTSTR)path);
            if(!ret)
                return "";
            return std::string(path) + "\\";
        }

        DWORD createDirectory(std::string dirName)
        {
            DWORD ret = CreateDirectory((LPCTSTR)dirName.c_str(), NULL);
            if(!ret)
               ret = GetLastError();
            return ret;
        }

        DWORD createPath(std::string fullPath)
        {
            for(char &c : fullPath)
            {
                if(c == '\\')
                {
                    c = '\0';
                    DWORD ret = createDirectory(fullPath);
                    c = '\\';
                    if(ret == ERROR_ALREADY_EXISTS || ret == ERROR_PATH_NOT_FOUND)
                    {
                        return -1;
                    }
                }
            }
            return 0;
        }

        template <class T>
        std::string WriteLog(const T &t)
        {
            std::string name = getCurrentDirectory() + timestamp::timestamp().getDateAndTime() + ".log";

            try{
                std::ofstream file(name);
                if(!file)
                    return "";
                std::ostringstream s;
                s << "[" << timestamp::timestamp().getDateAndTime() << "]" << t << std::endl;
                file << s.str();
                file.close(); 
                return name;
            }
            catch(...){
                return "";
            }
        }
       
        void WriteAppLog(const std::string &s)
        {
            std::ofstream file("AppLog.txt", std::ios::app);
            file << "[";
            file << timestamp::timestamp().getDateAndTime();
            file << "]" << "\n" << s << std::endl << "\n";
            file.close();
        }
    };
}

#endif //FILE_OPERATIONS_H