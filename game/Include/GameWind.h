#include <Windows.h>
#pragma once
/*+-------------------------------------------------
 *| <GameWind> 窗口管理类
 *| 2020/1/19
 *+-------------------------------------------------
 */

class GameWind{
public:
    HWND mHwnd;
private:
    int mWidth;
    int mHeight;
    HINSTANCE mhInstance;
    RECT wcRect;
public:
    GameWind(int width, int height,HINSTANCE hInstacne);
    ~GameWind();
    //创建窗口
    HRESULT Create(const char* className);
    //系统消息处理
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

