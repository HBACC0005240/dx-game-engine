#include "GameWind.h"
#include "Graphics.h"
#include <tchar.h> //swprintf_s

Graphics::Graphics(GameWind& wnd):wnd(wnd){
	OutputDebugString(L"Graphics()����\n");
	InitD3D();
}

Graphics::~Graphics()
{
	OutputDebugString(L"~Graphics()����\n");
	if (m_d3dDevice != nullptr)
	{
		m_d3dDevice->Release();
	}

	if (m_d3d9 != nullptr)
	{
		m_d3d9->Release();
	}
}

HRESULT Graphics::InitD3D()
{
	//����D3D����
	m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d9 == NULL) {
		return E_FAIL;
	}

	///��ȡ�Կ�ģʽ
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//У��Ӳ����������
	D3DCAPS9 caps;
	m_d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;//�Զ�ά����Ȼ���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//��Ȼ������ظ�ʽ[clearʱ���ZBUFFER]

	//����device�豸
	if (FAILED(m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd.mHwnd, vp, &d3dpp, &m_d3dDevice))) {
		return E_FAIL;
	}

	if (FAILED(D3DXCreateFont(m_d3dDevice, 24, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"΢���ź�", &m_d3dFont))) {
		return E_FAIL;
	}

	return S_OK;
}

void Graphics::Render()
{

	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

	m_d3dDevice->BeginScene();
	//-----------------------------
	wchar_t g_strFPS[50] = { 0 };
	int charCount = swprintf_s(g_strFPS, 20, TEXT("FPS:%0.2f (%d,%d)"), Getfps(), wnd.pt.x, wnd.pt.y);
	RECT formatRect;
	GetClientRect(wnd.mHwnd, &formatRect);
	m_d3dFont->DrawText(NULL, g_strFPS, charCount, &formatRect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 39, 136));

	//-----------------------------
	m_d3dDevice->EndScene();

	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

//����֡��
float Graphics::Getfps()
{
	static float fps = 0;   //������Ҫ�����FPSֵ
	static int frameCount = 0;//֡��
	static float currentTime = 0.0f;//��ǰʱ��
	static float lastTime = 0.0f;//����ʱ��
	frameCount++;
	currentTime = timeGetTime() * 0.001f;
	if (currentTime - lastTime > 1.0f) {
		fps = (float)frameCount / (currentTime - lastTime);
		lastTime = currentTime;
		frameCount = 0;
	}
	return fps;
}
