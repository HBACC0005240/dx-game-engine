#include <Windows.h>
#include "../Include/GameWind.h"

//入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	GameWind gGameWind(800, 600, hInstance);
	if (FAILED(gGameWind.Create("Game v1.0"))) {
		MessageBox(gGameWind.mHwnd, "消息提示", "窗口创建失败", MB_OK);
		return 0;
	}

	//5、通过循环取消息
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//若检测到需要处理消息则返回非0（包括WM_QUIT）
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			//获取当前运行时间（毫秒）
			//GameWind::GameUpdate();
		}

	}
}