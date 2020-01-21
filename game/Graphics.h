#pragma once
#include "Core.h"
#include "GameWind.h"

class Graphics {
private:
	GameWind& wnd;
	LPDIRECT3D9 m_d3d9;
	LPD3DXFONT m_d3dFont = nullptr;
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	Graphics(GameWind &wnd);
	~Graphics();
	HRESULT InitD3D();
	HRESULT InitVertex();
	void Render();
	float Getfps();
};