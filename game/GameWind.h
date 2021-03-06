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
    RECT clientRect;//客户去矩形
    static POINT pt;

    //按键函数指针
    bool (*KeyBoard)(char key, BUTTON_KEY bk);
    //鼠标按键函数指针
    bool (*keyMouse)(int x, int y, BUTTON_KEY bk);

    float mWidth;
    float mHeight;
private:
    bool isShow;
    HINSTANCE mhInstance = nullptr;
    static const wchar_t* wndClassName;
public:
    GameWind(HINSTANCE hInstacne, float width, float height);
    GameWind(const GameWind& wnd);
    ~GameWind();
    void ShowWind();
    bool ProcessMessage();
    void ShowMessageBox(const wchar_t* title, const wchar_t* msg);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

GameWind* CALL windCreate(HINSTANCE hInstance, float width, float hegiht);
