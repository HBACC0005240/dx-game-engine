#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")//d3d¡¥Ω”ø‚
#pragma comment(lib,"winmm.lib") //timeGetTime()
class Graphics {

private:
	GameWind& wnd;
	LPDIRECT3D9 m_d3d9;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPD3DXFONT m_d3dFont = nullptr;
public:
	Graphics(GameWind &wnd);
	~Graphics();
	HRESULT InitD3D();
	void Render();
	float Getfps();
};