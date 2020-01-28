#include "Core.h"
#include "GameWind.h"
#include "Game.h"

bool func1(int key) {
	wchar_t buf[50];
	swprintf_s(buf, TEXT("按键：%c"), key);
	OutputDebugString(buf);
	return false;
}
//入口函数
GameWind* g_wnd;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		g_wnd = windCreate(hInstance, 800.0f, 600.0f);
		try
		{
			//throw AHLIN::Exception(L"文件", 10,L"aaa");
			Game game(*g_wnd);

			g_wnd->KeyDown = func1;

			//初始化
			game.Init();

			//处理系统消息
			while (g_wnd->ProcessMessage())
			{
				//处理游戏循环逻辑
				game.Run();
				//显示窗口
				//wnd.ShowWind();
			}

		}
		catch (const AHLIN::Exception &e)
		{
			g_wnd->ShowMessageBox(L"错误信息", e.what());
		}
	}
	catch (const AHLIN::Exception &e)
	{
		MessageBox(nullptr, e.what(),L"错误信息", MB_OK);
	}
	catch (...) {
		MessageBox(nullptr, L"unknown error!", L"错误信息", MB_OK);
	}

	//delete g_wnd;
	return 0;
}