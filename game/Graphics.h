#pragma once
#include "Core.h"
#include "GameWind.h"
#include "Camera.h"
#include "DrawPoint.h"
#include "DrawLine.h"
#include "DrawGText.h"
#include "DrawTriangle.h"

class Graphics {
private:
	GameWind& wnd; //游戏窗口
	LPDIRECT3D9 m_d3d9;//d3d对象
	LPD3DXFONT m_d3dFont = nullptr;//文字对象
public:
	Camera* g_camera;//摄影机
	DrawPoint* g_point;//对象
	DrawLine* g_line;//对象
	DrawGText* g_text;//文字对象
	DrawTriangle* g_triangle;//三角形对象
	DrawTriangle* g_3dtriangle;//三角形对象
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;//设备对象
	Graphics(GameWind &wnd);
	~Graphics();
	HRESULT InitD3D();
	HRESULT InitVertex();
	void Render();
	float Getfps();
};