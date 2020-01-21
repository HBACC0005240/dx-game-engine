#include "Core.h"
#include "GameWind.h"
#include "Game.h"

//��ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		GameWind wnd(hInstance,800,600);
		try
		{
			//throw AHLIN::Exception(L"�ļ�", 10,L"aaa");
			Game game(wnd);
			//��ʼ��
			game.Init();

			//����ϵͳ��Ϣ
			while (wnd.ProcessMessage())
			{
				//������Ϸѭ���߼�
				game.Run();
				//��ʾ����
				//wnd.ShowWind();
			}

		}
		catch (const AHLIN::Exception &e)
		{
			wnd.ShowMessageBox(L"������Ϣ", e.what());
		}
	}
	catch (const AHLIN::Exception &e)
	{
		MessageBox(nullptr, e.what(),L"������Ϣ", MB_OK);
	}
	catch (...) {
		MessageBox(nullptr, L"unknown error!", L"������Ϣ", MB_OK);
	}

	return 0;
}