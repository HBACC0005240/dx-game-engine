#include "Graphics.h"
//初始化
int pX = 323, pY = 283;
bool keyW = false, keyA = false,keyS = false, keyD = false, keyQ = false, keyR = false;
//是否可以一直移动
bool IS_KEY_DOWN = false;
Graphics::Graphics(GameWind& wnd):wnd(wnd){

	OutputDebugString(L"Graphics()构造\n");
	InitD3D();

	//初始化摄影机
	g_camera = new Camera(m_d3dDevice);

	//点
	g_point = new DrawPoint(m_d3dDevice);

	//线
	g_line = new DrawLine(m_d3dDevice);

	//初始化字体类
	g_text = new DrawGText(m_d3dFont);

	//初始化
	g_triangle = new DrawTriangle(m_d3dDevice);

	//初始化
	g_3dtriangle = new DrawTriangle(m_d3dDevice);

	//加载人物图片
	//char file[] = ".\\Data\\hum";
	//char file[] = ".\\Data\\hum2";
	//char file[] = ".\\Data\\hum3";
	//char file[] = ".\\Data\\items";
	//pWzlHum = new GWzlData(file);
	//g_player = new GPlayer(pWzlHum, 0, 0, m_d3dDevice);

	//创建地图
	char map[] = "0";
	g_map = new GMap(map, m_d3dDevice,m_d3dFont);

	//指定通知函数
	wnd.KeyBoard = GMap::KeyBoard;
	wnd.keyMouse = GMap::keyMouse;

	//创建动画
	//char wzlfile[] = ".\\Data\\Objects";
	//pWzlAni = new GWzlData(wzlfile);
	//g_Ani = new GAnimation(2723, 10, pWzlAni,m_d3dDevice);
	//g_Ani->Load();

	//GWzlDraw::OpenSaveBmp();
}

Graphics::~Graphics()
{
	if (m_d3dDevice != nullptr)
	{
		m_d3dDevice->Release();
	}

	if (m_d3d9 != nullptr)
	{
		m_d3d9->Release();
	}

	delete g_point;
	delete g_line;
	delete g_camera;
	delete g_text;
	delete g_triangle;
	delete g_3dtriangle;

	delete pWzlHum;
	//delete g_player;
	OutputDebugString(L"~Graphics()析构\n");
}

HRESULT Graphics::InitD3D()
{
	//创建D3D对象
	m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d9 == NULL) {
		return E_FAIL;
	}

	///获取显卡模式
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//校验硬件顶点运算
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
	//d3dpp.EnableAutoDepthStencil = TRUE;//自动维护深度缓存
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//深度缓存像素格式[clear时清除ZBUFFER] D3DCLEAR_ZBUFFER

	//创建device设备
	if (FAILED(m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd.mHwnd, vp, &d3dpp, &m_d3dDevice))) {
		return E_FAIL;
	}

	if (FAILED(D3DXCreateFont(m_d3dDevice, 20, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"微软雅黑", &m_d3dFont))) {
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Graphics::InitVertex()
{
	//创建顶点缓存
	g_point->CreateVectex();

	//创建顶点缓存
	//g_line->CreateVectex();

	//创建三角形顶点缓存
	//g_triangle->CreateVectex();

	//创建3D三角形
	g_3dtriangle->Create3DVectex();
	//g_3dtriangle->setIndices();

	//加载图片
	//g_player->Load(STAND,DOWN);

	//加载地图
	g_map->Load();

	return S_OK;
}

void Graphics::Render()
{

	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

	m_d3dDevice->BeginScene();
	//-----------------------------

	//按键
	KeyDown();

	//绘制地图
	g_map->Show(pX, pY);

	//画线列表
	//g_line->Draw(400.0f, 250.0f, 400.0f, 350.0f, 0xffffffff);
	//g_line->Draw(350.0f, 300.0f, 450.0f, 300.0f, 0xffffffff);

	//绘制人物
	//g_player->Show();

	//绘制动画
	//g_Ani->Show(100,100);

	//--------------------------------------------------------------
	//重置
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_d3dDevice->SetTexture(0, NULL);
	//--------------------------------------------------------------
	//视图
	g_camera->SetMatrices(wnd.mWidth, wnd.mHeight);
	g_camera->SetTransform(GTime::GetCountDown());
	//--------------------------------------------------------------
	//画点列表
	//g_point->Draw();

	//画三角形
	//g_triangle->Draw(100,100,0xffffffff);

	//画3d三角形
	//g_3dtriangle->Draw3D();
	//g_3dtriangle->DrawIndex3D();

	//KeyDown();
	//--------------------------------------------------------------
	//绘制时间
	//wsprintf(pos, L"人物状态：s:%d,f:%d", g_player->mState, g_player->mFrame);
	//g_text->Draw(pos, 0, 60, 800, 600, 0xffffffff);

	wchar_t pos[50] = { 0 };

	//绘制FPS
	g_text->DrawFps(Getfps(), &wnd.clientRect, 0xffffffff);

	//绘制鼠标
	wsprintf(pos, L"坐标：[%d,%d]", wnd.pt.x, wnd.pt.y);
	g_text->Draw(pos, 0, 20, 800, 600, 0xffffffff);

	//绘制时间
	wsprintf(pos, L"time：[%d]-[%d]", GTime::s_tNowTime, GTime::s_tPrevTime);
	g_text->Draw(pos, 0, 40, 800, 600, 0xffffffff);

	//屏幕宽高
	wsprintf(pos, L"wh：[%d,%d]", static_cast<int>(wnd.mWidth), static_cast<int>(wnd.mHeight));
	g_text->Draw(pos, 0, 80, 800, 600, 0xffffffff);

	//说明
	g_text->Draw(L"移动：[左键]-行走 [右键]-跑步", 0, 100, 800, 600, 0xffffffff);
	g_text->Draw(L"绘制：[F]-Tiles [G]-SmTiles [H]-Objects [J]-Animation [K]-坐标线", 0, 120, 800, 600, 0xffffffff);
	//-----------------------------
	m_d3dDevice->EndScene();

	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

//计算帧数
float Graphics::Getfps()
{
	static float fps = 0;   //我们需要计算的FPS值
	static int frameCount = 0;//帧数
	static float currentTime = 0.0f;//当前时间
	static float lastTime = 0.0f;//持续时间
	frameCount++;
	currentTime = timeGetTime() * 0.001f;
	if (currentTime - lastTime > 1.0f) {
		fps = (float)frameCount / (currentTime - lastTime);
		lastTime = currentTime;
		frameCount = 0;
	}
	return fps;
}

void Graphics::KeyDown()
{
	//W
	if (::GetAsyncKeyState(0x57) & 0x8000f) {
		if (keyW)
		{
			pY -= 1;
			keyW = IS_KEY_DOWN;
		}
	}
	else {
		keyW = true;
	}
	//A
	if (::GetAsyncKeyState(0x41) & 0x8000f) {
		if (keyA)
		{
			pX -= 1;
			keyA = IS_KEY_DOWN;
		}
	}
	else {
		keyA = true;
	}

	//S
	if (::GetAsyncKeyState(0x53) & 0x8000f) {
		if (keyS)
		{
			pY += 1;
			keyS = IS_KEY_DOWN;
		}
	}
	else {
		keyS = true;
	}
	//D
	if (::GetAsyncKeyState(0x44) & 0x8000f) {
		if (keyD)
		{
			pX += 1;
			keyD = IS_KEY_DOWN;
		}
	}
	else {
		keyD = true;
	}
	//Q
	if (::GetAsyncKeyState(0x51) & 0x8000f) {
		if (keyQ)
		{
			pX = 0;
			keyQ = IS_KEY_DOWN;
		}
	}
	else {
		keyQ = true;
	}
	//R
	if (::GetAsyncKeyState(0x45) & 0x8000f) {
		if (keyR)
		{
			pY = 0;
			keyR = IS_KEY_DOWN;
		}
	}
	else {
		keyR = true;
	}

}
