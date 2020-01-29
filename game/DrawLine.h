#pragma once
#include "Core.h"

//顶点格式
#define D3DFVF_VERTEX_LINE (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class DrawLine {
private:
	//顶点结构
	struct VertexLine
	{
		float x, y, z,rhw;
		DWORD color;
	};
	LPDIRECT3DDEVICE9 p_d3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
public:
	DrawLine(LPDIRECT3DDEVICE9 d3dDevice);
	~DrawLine();
	HRESULT CreateVectex(float x, float y, float x1, float y1, DWORD color);
	void Draw(float x, float y, float x1, float y1, DWORD color);
};