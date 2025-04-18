#include "WindowsDisplay.h"

// Window class name
const char* WINDOW_CLASS_NAME = "EdenEngineWindow";

WindowsDisplay::WindowsDisplay() : hwnd(nullptr), hInstance(nullptr) {}

WindowsDisplay::~WindowsDisplay() {
    if (hwnd) {
        DestroyWindow(hwnd);
    }
}

LRESULT CALLBACK WindowsDisplay::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void WindowsDisplay::Initialize() {
    // Get the instance handle
    hInstance = GetModuleHandle(nullptr);

    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Create the window
    hwnd = CreateWindowEx(
        0,
        WINDOW_CLASS_NAME,
        "Eden Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return;
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void WindowsDisplay::Run() {
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
