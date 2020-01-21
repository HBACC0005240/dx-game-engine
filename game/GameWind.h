#include "Core.h"
#pragma once
/*+-------------------------------------------------
 *| <GameWind> 窗口管理类
 *| 2020/1/19
 *+-------------------------------------------------
 */

class GameWind{
public:
    HWND mHwnd;
    RECT wcRect;
    static POINT pt;
private:
    bool isShow;
    int mWidth;
    int mHeight;
    HINSTANCE mhInstance = nullptr;
    static const wchar_t* wndClassName;
public:
    GameWind(HINSTANCE hInstacne, int width, int height);
    GameWind(const GameWind& wnd);
    ~GameWind();
    void ShowWind();
    bool ProcessMessage();
    void ShowMessageBox(const wchar_t* title, const wchar_t* msg);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

