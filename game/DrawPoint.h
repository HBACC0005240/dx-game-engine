#pragma once
#include "Core.h"

//顶点格式
#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class DrawPoint {
private:
	//顶点结构
	struct VertexPoint
	{
		float x, y, z, rhw;
		DWORD color;
	};
	LPDIRECT3DDEVICE9 p_d3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
public:
	DrawPoint(LPDIRECT3DDEVICE9 g_d3dDevice);
	~DrawPoint();
	HRESULT CreateVectex();
	void Draw();
};