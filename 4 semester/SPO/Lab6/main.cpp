#include "windows.h"
#include "stdio.h"

#define VK_Q 0x51
HHOOK hhkLowLevelKybd;
HANDLE console;
CONSOLE_SCREEN_BUFFER_INFO info;
bool ENABLED = false;
bool L_PRESSED = false;
bool R_PRESSED = false;
bool CTRL_PRESSED = false;
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0) return CallNextHookEx(hhkLowLevelKybd, nCode, wParam, lParam);
    KBDLLHOOKSTRUCT *l = (KBDLLHOOKSTRUCT *)lParam;

    switch (wParam)
    {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: {
            if (CTRL_PRESSED && (l->vkCode == VK_Q)) {
                ENABLED = !ENABLED;
            }
            if (ENABLED) {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                printf("+%ld\n", l->vkCode);
                SetConsoleTextAttribute(console, info.wAttributes);
            }
            L_PRESSED = l->vkCode == VK_LCONTROL || L_PRESSED;
            R_PRESSED = l->vkCode == VK_RCONTROL || R_PRESSED;
            CTRL_PRESSED = L_PRESSED || R_PRESSED || CTRL_PRESSED;
            break;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            L_PRESSED = l->vkCode != VK_LCONTROL && L_PRESSED;
            R_PRESSED = l->vkCode != VK_RCONTROL && R_PRESSED;
            CTRL_PRESSED = L_PRESSED || R_PRESSED;
            if (ENABLED) {
                SetConsoleTextAttribute(console, FOREGROUND_RED);
                printf("-%ld\n", l->vkCode);
                SetConsoleTextAttribute(console, info.wAttributes);
            }
            break;
        }
    }
    return CallNextHookEx(hhkLowLevelKybd, nCode, wParam, lParam);
}

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE hStatus;
int main(DWORD argc, LPTSTR argv[])
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &info);
    // Install the low-level keyboard & mouse hooks
    hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

    // Keep this app running until we're told to stop
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    printf("Ping!\n");
    UnhookWindowsHookEx(hhkLowLevelKybd)
    SetConsoleTextAttribute(console, info.wAttributes);
    CloseHandle(console);
    return 0;
}