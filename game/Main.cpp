#include "Core.h"
#include "GameWind.h"
#include "Game.h"

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		GameWind wnd(hInstance,800,600);
		try
		{
			//throw AHLIN::Exception(L"文件", 10,L"aaa");
			Game game(wnd);
			//初始化
			game.Init();

			//处理系统消息
			while (wnd.ProcessMessage())
			{
				//处理游戏循环逻辑
				game.Run();
				//显示窗口
				//wnd.ShowWind();
			}

		}
		catch (const AHLIN::Exception &e)
		{
			wnd.ShowMessageBox(L"错误信息", e.what());
		}
	}
	catch (const AHLIN::Exception &e)
	{
		MessageBox(nullptr, e.what(),L"错误信息", MB_OK);
	}
	catch (...) {
		MessageBox(nullptr, L"unknown error!", L"错误信息", MB_OK);
	}

	return 0;
}