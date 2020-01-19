#include "../Include/GameWind.h"

//构造函数
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

//创建窗口
HRESULT GameWind::Create(const char* className)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;										//类额外的内存，通常为零
	wc.cbWndExtra = 0;										//窗口额外的内存，通常为零
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//设置背景
	wc.hCursor = LoadCursor(NULL, IDC_HAND);				//设置光标，如果第一个参数为NULL，代表使用系统提供的默认光标
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);					//LOGO
	wc.hInstance = mhInstance;								//当前实例句柄，WinMain函数中形参即可
	wc.lpfnWndProc = GameWind::WindowProc;							//窗口过程函数，回调函数，名称可以随便起
	wc.lpszClassName = className;							//指定窗口类名
	wc.lpszMenuName = NULL;									//菜单名，没有填NULL
	wc.style = 0;											//0代表默认风格


	//注册窗口
	RegisterClass(&wc);

	//计算客户区大小
	SetRect(&wcRect, 0, 0, mWidth, mHeight);
	AdjustWindowRect(&wcRect, WS_OVERLAPPEDWINDOW, false);

	//3、创建窗口
	mHwnd = CreateWindow(
		wc.lpszClassName,		//类名
		className,				//窗口名
		WS_OVERLAPPEDWINDOW,	//显示风格  WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT,			//起始坐标 x CW_USEDEFAULT
		CW_USEDEFAULT,			//起始坐标 y CW_USEDEFAULT
		wcRect.right - wcRect.left,					//窗口宽度 nWidth
		wcRect.bottom - wcRect.top,					//窗口高度 nHeight
		NULL,					//父窗口，NULL
		NULL,					//菜单  NULL
		mhInstance,				//实例句柄，hInstance
		NULL					//其他参数   NULL
	);

	if (mHwnd == NULL)
	{
		return E_FAIL;
	}

	//4、显示和更新
	ShowWindow(mHwnd, SW_SHOWNORMAL);

	UpdateWindow(mHwnd);

	return S_OK;
}

//窗口消息处理回调
LRESULT CALLBACK GameWind::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	TCHAR buf[1024];
	HDC hdc;
	INT index = 0;

	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);                //触发WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);                  //发送退出消息
		break;
	case WM_LBUTTONDOWN:                      //鼠标左键按下消息
	{
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	}
	case WM_KEYDOWN:       //键盘消息
	{
		wsprintf(buf, "键盘按下:%c\n", wParam);
		OutputDebugString(buf);
		break;
	}
	case WM_MOUSEMOVE:
	{
		pt.x = LOWORD(lParam); //取得x的坐标
		pt.y = HIWORD(lParam); //取得y的坐标

		//填充数据
		wsprintf(buf, TEXT("%d,%d"), pt.x, pt.y);
		hdc = GetDC(hwnd);
		//输出字符串
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
	//默认方式处理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

