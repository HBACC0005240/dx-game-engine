#pragma once
#include "Core.h"

//顶点格式
#define D3DFVF_TRIANGLE (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define D3DFVF_3D_TRIANGLE (D3DFVF_XYZ|D3DFVF_DIFFUSE)

class DrawTriangle {
private:
	//顶点结构
	struct VertexTriangle
	{
		float x, y, z, rhw;
		DWORD color;
	};
	struct Vertex3DTriangle
	{
		float x, y, z;
		DWORD color;
	};
	LPDIRECT3DDEVICE9 p_d3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
public:
	DrawTriangle(LPDIRECT3DDEVICE9 d3dDevice);
	~DrawTriangle();
	HRESULT CreateVectex(float x, float y ,DWORD color);
	HRESULT Create3DVectex();
	void Draw(float x, float y, DWORD color);
	void Draw3D();
};