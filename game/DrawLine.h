#pragma once
#include "Core.h"

//�����ʽ
#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

class DrawLine {
private:
	//����ṹ
	struct VertexLine
	{
		float x, y, z, rhw;
		DWORD color;
	};
	LPDIRECT3DDEVICE9 p_d3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
public:
	DrawLine(LPDIRECT3DDEVICE9 d3dDevice);
	~DrawLine();
	HRESULT CreateVectex();
	void Draw();
};