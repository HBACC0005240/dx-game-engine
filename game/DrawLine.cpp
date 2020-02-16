#include "DrawLine.h"

DrawLine::DrawLine(LPDIRECT3DDEVICE9 d3dDevice)
	:
	g_pVB(NULL),
	p_d3dDevice(d3dDevice)
{
	OutputDebugString(L"DrawLine()构造\n");
}

DrawLine::~DrawLine()
{
	OutputDebugString(L"~DrawLine()析构\n");
}

//初始化顶点缓存
HRESULT DrawLine::CreateVectex(float x,float y,float x1,float y1,DWORD color)
{
	//顶点
	//DWORD color1 = 0xffffffff;
	//DWORD color2 = 0xff00ff00;
	VertexLine vertex[] = {
		{x, y, 0.0f,1.0f,  color},
		{ x1, y1, 0.0f, 1.0f, color},
	};

	if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(vertex), 0, D3DFVF_VERTEX_LINE, D3DPOOL_DEFAULT, &g_pVB, NULL))) {
		return E_FAIL;
	}
	//throw AHLIN::Exception(_FILE, _LINE, L"创建point顶点缓存失败");

	void* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertex), &pVertices, 0))) {
		return E_FAIL;
	}

	memcpy(pVertices, vertex, sizeof(vertex));

	g_pVB->Unlock();

	return S_OK;
}

//绘制点列表
void DrawLine::Draw(float x, float y, float x1, float y1, DWORD color)
{
	CreateVectex(x,y,x1,y1,color);
	//设置贴图	
	p_d3dDevice->SetTexture(0, NULL);

	p_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexLine));
	g_pVB->Release();
	p_d3dDevice->SetFVF(D3DFVF_VERTEX_LINE);
	p_d3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}
