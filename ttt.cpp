#include <windows.h>
#include <shlwapi.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdint>
#pragma comment(lib,"shlwapi.lib")
namespace fs = std::filesystem;

#define BTN_TOR     1
#define BTN_CLEAN   2
#define BTN_PANIC   3
#define BTN_EXIT    4

HWND hLog;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

std::string GetExeFolder() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    if(pos != std::string::npos)
        path = path.substr(0, pos);
    return path;
}

void LogAction(const std::string& msg) {
    if(hLog) {
        std::string text;
        int len = GetWindowTextLengthA(hLog);
        if(len > 0) {
            char* buf = new char[len+1];
            GetWindowTextA(hLog, buf, len+1);
            text = buf;
            delete[] buf;
        }
        text += msg + "\r\n";
        SetWindowTextA(hLog, text.c_str());
        SendMessageA(hLog, EM_SCROLLCARET, 0, 0);
    }
}

void PrepareUSB() {
    std::string base = GetExeFolder();
    fs::create_directories(base + "\\tools\\tor-portable\\Browser");
    fs::create_directories(base + "\\panic");
    fs::create_directories(base + "\\config");
    std::ofstream(base + "\\tools\\cleanup.ps1").close();
    std::ofstream(base + "\\panic\\panic_wipe.ps1").close();
    std::ofstream(base + "\\config\\settings.json").close();
    std::ofstream(base + "\\config\\panic.flag").close();
    LogAction("Arborescence USB préparée.");
}

void RunTor() {
    std::string path = GetExeFolder() + "\\tools\\tor-portable\\Browser\\firefox.exe";
    HINSTANCE res = ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOW);
    if(reinterpret_cast<intptr_t>(res) <= 32)
        LogAction("Erreur: Tor Portable non trouvé !");
    else
        LogAction("Tor Portable lancé.");
}

void RunPowerShellScript(const std::string& relativePath, const std::string& actionName) {
    std::string base = GetExeFolder();
    std::string fullScript = base + "\\" + relativePath;
    std::string cmd = "-NoProfile -ExecutionPolicy Bypass -File \"" + fullScript + "\"";
    ShellExecuteA(NULL, "open", "powershell.exe", cmd.c_str(), NULL, SW_SHOW);
    LogAction(actionName + " lancé.");
}

void RunCleanup() { RunPowerShellScript("tools\\cleanup.ps1", "Nettoyage complet"); }
void RunPanic() { RunPowerShellScript("panic\\panic_wipe.ps1", "Panic Button"); }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    PrepareUSB();
    const char CLASS_NAME[] = "USBAnonLauncher";
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "USB Anonymisation Launcher",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
        NULL, NULL, hInstance, NULL
    );

    CreateWindowA("button", "Lancer Tor Portable",
        WS_VISIBLE | WS_CHILD, 80, 30, 220, 32,
        hwnd, (HMENU)BTN_TOR, hInstance, NULL);
    CreateWindowA("button", "Nettoyage Complet",
        WS_VISIBLE | WS_CHILD, 80, 80, 220, 32,
        hwnd, (HMENU)BTN_CLEAN, hInstance, NULL);
    CreateWindowA("button", "PANIC BUTTON",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 80, 130, 220, 32,
        hwnd, (HMENU)BTN_PANIC, hInstance, NULL);
    CreateWindowA("button", "Fermer",
        WS_VISIBLE | WS_CHILD, 80, 180, 220, 32,
        hwnd, (HMENU)BTN_EXIT, hInstance, NULL);

    hLog = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        20, 230, 360, 140,
        hwnd, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while(GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case BTN_TOR:   RunTor(); break;
                case BTN_CLEAN: RunCleanup(); break;
                case BTN_PANIC: RunPanic(); break;
                case BTN_EXIT:  DestroyWindow(hwnd); break;
            }
            return 0;

        case WM_CTLCOLORBTN:
        {
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(0, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }

        case WM_CTLCOLORSTATIC:
        {
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(0, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }

        case WM_ERASEBKGND:
        {
            HDC hdc = (HDC)wParam;
            RECT rc;
            GetClientRect(hwnd, &rc);
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);
            return 1;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
