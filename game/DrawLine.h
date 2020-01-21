#pragma once
#include "Graphics.h"
//顶点结构
struct VertexLine
{
	float x, y, z, rhw;
	DWORD color;
};

//顶点格式
#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class DrawLine {
public:
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
private:
	Graphics& gfx;
public:
	DrawLine(Graphics& gfx);
	~DrawLine();
	HRESULT CreateVectex();
	void Draw();
};