#include "Core.h"
#include "GameWind.h"
#include "Game.h"

bool func1(int key) {
	wchar_t buf[50];
	swprintf_s(buf, TEXT("������%c"), key);
	OutputDebugString(buf);
	return false;
}
//��ں���
GameWind* g_wnd;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		g_wnd = windCreate(hInstance, 800.0f, 600.0f);
		try
		{
			//throw AHLIN::Exception(L"�ļ�", 10,L"aaa");
			Game game(*g_wnd);

			g_wnd->KeyDown = func1;

			//��ʼ��
			game.Init();

			//����ϵͳ��Ϣ
			while (g_wnd->ProcessMessage())
			{
				//������Ϸѭ���߼�
				game.Run();
				//��ʾ����
				//wnd.ShowWind();
			}

		}
		catch (const AHLIN::Exception &e)
		{
			g_wnd->ShowMessageBox(L"������Ϣ", e.what());
		}
	}
	catch (const AHLIN::Exception &e)
	{
		MessageBox(nullptr, e.what(),L"������Ϣ", MB_OK);
	}
	catch (...) {
		MessageBox(nullptr, L"unknown error!", L"������Ϣ", MB_OK);
	}

	//delete g_wnd;
	return 0;
}