#include <Windows.h>
#pragma once
/*+-------------------------------------------------
 *| <GameWind> ���ڹ�����
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
    //��������
    HRESULT Create(const char* className);
    //ϵͳ��Ϣ����
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

