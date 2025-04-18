#pragma once

#include <Windows.h>

class WindowsDisplay {
private:
    HWND hwnd;
    HINSTANCE hInstance;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    WindowsDisplay();
    ~WindowsDisplay();

    void Initialize();
    void Run();
}; 