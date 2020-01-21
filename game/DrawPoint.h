#pragma once
#include "Graphics.h"
//顶点结构
struct VertexPoint
{
	float x, y, z,rhw;
	DWORD color;
};

//顶点格式
#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class DrawPoint {
public:
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
private:
	Graphics& gfx;
public:
	DrawPoint(Graphics& gfx);
	~DrawPoint();
	HRESULT CreateVectex();
	void Draw();
};