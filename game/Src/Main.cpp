#include <Windows.h>
#include "../Include/GameWind.h"

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	GameWind gGameWind(800, 600, hInstance);
	if (FAILED(gGameWind.Create("Game v1.0"))) {
		MessageBox(gGameWind.mHwnd, "��Ϣ��ʾ", "���ڴ���ʧ��", MB_OK);
		return 0;
	}

	//5��ͨ��ѭ��ȡ��Ϣ
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//����⵽��Ҫ������Ϣ�򷵻ط�0������WM_QUIT��
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			//��ȡ��ǰ����ʱ�䣨���룩
			//GameWind::GameUpdate();
		}

	}
}