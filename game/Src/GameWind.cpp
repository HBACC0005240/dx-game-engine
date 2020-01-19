#include "../Include/GameWind.h"

//���캯��
GameWind::GameWind(int width, int height, HINSTANCE hInstacne)
{
	mWidth = width;
	mHeight = height;
	mhInstance = hInstacne;
	mHwnd = NULL;
	wcRect = { 0,0,0,0 };
}

GameWind::~GameWind()
{

}

//��������
HRESULT GameWind::Create(const char* className)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;										//�������ڴ棬ͨ��Ϊ��
	wc.cbWndExtra = 0;										//���ڶ�����ڴ棬ͨ��Ϊ��
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ñ���
	wc.hCursor = LoadCursor(NULL, IDC_HAND);				//���ù�꣬�����һ������ΪNULL������ʹ��ϵͳ�ṩ��Ĭ�Ϲ��
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);					//LOGO
	wc.hInstance = mhInstance;								//��ǰʵ�������WinMain�������βμ���
	wc.lpfnWndProc = GameWind::WindowProc;							//���ڹ��̺������ص����������ƿ��������
	wc.lpszClassName = className;							//ָ����������
	wc.lpszMenuName = NULL;									//�˵�����û����NULL
	wc.style = 0;											//0����Ĭ�Ϸ��


	//ע�ᴰ��
	RegisterClass(&wc);

	//����ͻ�����С
	SetRect(&wcRect, 0, 0, mWidth, mHeight);
	AdjustWindowRect(&wcRect, WS_OVERLAPPEDWINDOW, false);

	//3����������
	mHwnd = CreateWindow(
		wc.lpszClassName,		//����
		className,				//������
		WS_OVERLAPPEDWINDOW,	//��ʾ���  WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT,			//��ʼ���� x CW_USEDEFAULT
		CW_USEDEFAULT,			//��ʼ���� y CW_USEDEFAULT
		wcRect.right - wcRect.left,					//���ڿ�� nWidth
		wcRect.bottom - wcRect.top,					//���ڸ߶� nHeight
		NULL,					//�����ڣ�NULL
		NULL,					//�˵�  NULL
		mhInstance,				//ʵ�������hInstance
		NULL					//��������   NULL
	);

	if (mHwnd == NULL)
	{
		return E_FAIL;
	}

	//4����ʾ�͸���
	ShowWindow(mHwnd, SW_SHOWNORMAL);

	UpdateWindow(mHwnd);

	return S_OK;
}

//������Ϣ����ص�
LRESULT CALLBACK GameWind::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	TCHAR buf[1024];
	HDC hdc;
	INT index = 0;

	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);                //����WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);                  //�����˳���Ϣ
		break;
	case WM_LBUTTONDOWN:                      //������������Ϣ
	{
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	}
	case WM_KEYDOWN:       //������Ϣ
	{
		wsprintf(buf, "���̰���:%c\n", wParam);
		OutputDebugString(buf);
		break;
	}
	case WM_MOUSEMOVE:
	{
		pt.x = LOWORD(lParam); //ȡ��x������
		pt.y = HIWORD(lParam); //ȡ��y������

		//�������
		wsprintf(buf, TEXT("%d,%d"), pt.x, pt.y);
		hdc = GetDC(hwnd);
		//����ַ���
		TextOut(hdc, 0, 0, buf, lstrlen(buf));
		ReleaseDC(hwnd, hdc);

		break;
	}
	case WM_PAINT:     
	{
		break;
	}
	default:
		break;
	}
	//Ĭ�Ϸ�ʽ����
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

