#include <windows.h>

#pragma comment(lib, "User32.lib")

inline void MinForegroundWindow() {
    HWND foreWND = GetForegroundWindow();
    ShowWindow(foreWND, SW_FORCEMINIMIZE);
}

inline void OpenDistraction() {
    HWND totallyWorking = FindWindow(NULL, "Command Prompt"); // Hardcoded window title (for now)
    ShowWindow(totallyWorking, SW_MAXIMIZE);
}

int main () {
    if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x43)) {
        MessageBox(NULL, "Hotkey CTRL+ALT+C has been set", "Success", MB_OK);
    }
    else {
        MessageBox(NULL, "Hotkey failed to register", "Error", MB_OK);
        return 0;
    }
 
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) { // condition will fail once WM_QUIT message is posted to the queue
        switch (msg.message) {
            case WM_HOTKEY: // Possible to check for specific hotkey presses (lParam values)
                MinForegroundWindow();
                OpenDistraction();
                break;
        }
    }
    return 0;
}

// MSDN example: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerhotkey?redirectedfrom=MSDN