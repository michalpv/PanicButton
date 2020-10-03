#include <windows.h>

#pragma comment(lib, "User32.lib")

inline void MinForegroundWindow() {
    HWND foreWND = GetForegroundWindow();
    ShowWindow(foreWND, SW_FORCEMINIMIZE);
}

inline void OpenDistraction(HWND workWindow) {
    SetForegroundWindow(workWindow); // Brings window to the front if it is hidden behind other windows
    ShowWindow(workWindow, SW_MAXIMIZE);
}

int main () {
    FreeConsole(); // Will need to kill process from task manager
    HWND workWND;
    if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x56) && // CTRL+ALT+V
        RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x53)) { // CTRL+ALT+S
        MessageBox(NULL, "Hotkeys have been set", "Success", MB_OK);
    }
    else {
        MessageBox(NULL, "Hotkeys failed to register", "Error", MB_OK);
        return 0;
    }
 
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) { // Condition will fail once WM_QUIT message is posted to the queue
        switch (msg.message) {
            case WM_HOTKEY: // Possible to check for specific hotkey presses (lParam values)
                if (msg.wParam == 2) { // Hotkey to mark foreground window as work window
                    workWND = GetForegroundWindow();
                }
                else if (msg.wParam == 1) { // Panic hotkey
                    MinForegroundWindow();
                    OpenDistraction(workWND);
                }
                break;
        }
    }
    return 0;
}

// MSDN example: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerhotkey?redirectedfrom=MSDN