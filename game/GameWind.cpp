#include "GameWind.h"

const wchar_t* GameWind::wndClassName = L"Game v2.0";
POINT GameWind::pt = {0,0};

GameWind* gWnd;

GameWind* windCreate(HINSTANCE hInstance,float width, float hegiht) {
	if ( !gWnd)
	{
		gWnd = new GameWind(hInstance, width, hegiht);
		return gWnd;
	}
	return gWnd;
}

/*+---------------------------------------------------
 *| ��������
 *+---------------------------------------------------
 */
GameWind::GameWind(HINSTANCE hInstacne, float width, float height)
	:
	mhInstance(hInstacne),
	mWidth(width),
	mHeight(height),
	isShow(false),
	wcRect({0}),
	clientRect({0})
{
	OutputDebugString(L"GameWind()����\n");
	//1������
	WNDCLASS wc;
	wc.cbClsExtra = 0;										//�������ڴ棬ͨ��Ϊ��
	wc.cbWndExtra = 0;										//���ڶ�����ڴ棬ͨ��Ϊ��
	wc.hbrBackground = NULL;// (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ñ���
	wc.hCursor = LoadCursor(NULL, IDC_HAND);				//���ù�꣬�����һ������ΪNULL������ʹ��ϵͳ�ṩ��Ĭ�Ϲ��
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);					//LOGO
	wc.hInstance = mhInstance;								//��ǰʵ�������WinMain�������βμ���
	wc.lpfnWndProc = GameWind::WindowProc;							//���ڹ��̺������ص����������ƿ��������
	wc.lpszClassName = wndClassName;							//ָ����������
	wc.lpszMenuName = NULL;									//�˵�����û����NULL
	wc.style = 0;											//0����Ĭ�Ϸ��

	//2��ע�ᴰ��
	RegisterClass(&wc);

	//3������ͻ�����С
	wcRect = { 0,0,0,0 };
	int mX = 10, mY = 40;
	SetRect(&wcRect, mX, mY, static_cast<int>(mWidth) + mX, static_cast<int>(mHeight) + mY);
	AdjustWindowRect(&wcRect, WS_OVERLAPPEDWINDOW, false);

	//4����������
	mHwnd = CreateWindow(
		wc.lpszClassName,				//����
		wndClassName,						//������
		WS_OVERLAPPEDWINDOW,			//��ʾ���  WS_OVERLAPPEDWINDOW
		wcRect.left,					//��ʼ���� x CW_USEDEFAULT
		wcRect.top,						//��ʼ���� y CW_USEDEFAULT
		wcRect.right - wcRect.left,		//���ڿ�� nWidth
		wcRect.bottom - wcRect.top,		//���ڸ߶� nHeight
		NULL,							//�����ڣ�NULL
		NULL,							//�˵�  NULL
		mhInstance,						//ʵ�������hInstance
		NULL							//��������   NULL
	);

	if (mHwnd == NULL)
	{
		throw AHLIN::Exception(_FILE,_LINE,L"���ڴ���ʧ�ܣ�");
	}

	GetClientRect(mHwnd, &clientRect);

	//5����ʾ�͸���
	ShowWindow(mHwnd, SW_SHOWDEFAULT);
	UpdateWindow(mHwnd);
}

GameWind::GameWind(const GameWind& wnd)
{
	OutputDebugString(L"GameWind()��������\n");
	mHwnd = wnd.mHwnd;
	mhInstance = wnd.mhInstance;
	mWidth = wnd.mWidth;
	mHeight = wnd.mHeight;
	wcRect = wnd.wcRect;
}

GameWind::~GameWind()
{
	OutputDebugString(L"~GameWind()����\n");
	UnregisterClass(wndClassName, mhInstance);
}

void GameWind::ShowWind()
{
	isShow = IsWindowVisible(mHwnd);
	if ( ! isShow)
	{
		//5����ʾ�͸���
		ShowWindow(mHwnd, SW_SHOWDEFAULT);
		UpdateWindow(mHwnd);
	}
}
/**
 * ����ϵͳ��Ϣ
 */
bool GameWind::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

void GameWind::ShowMessageBox(const wchar_t* title, const wchar_t* msg)
{
	MessageBox(mHwnd, msg, title, MB_OK);
}

//������Ϣ����ص�
LRESULT CALLBACK GameWind::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	TCHAR buf[1024];
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);                //����WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);                  //�����˳���Ϣ
		break;
	case WM_SIZE:
	{
		if (gWnd)
		{
			float width = LOWORD(lParam);
			float height = HIWORD(lParam);
			gWnd->mWidth = width;
			gWnd->mHeight = height;
		}
		break;
	}
	case WM_LBUTTONDOWN:                      //������������Ϣ
	{
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	}
	case WM_KEYDOWN:       //������Ϣ
	{
		//wsprintf(buf, L"���̰���:%c\n", wParam);
		//OutputDebugString(buf);
		//gWnd->KeyDown((int)wParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		pt.x = LOWORD(lParam); //ȡ��x������
		pt.y = HIWORD(lParam); //ȡ��y������
		break;
	}
	default:
		break;
	}
	//Ĭ�Ϸ�ʽ����
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

