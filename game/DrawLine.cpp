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
HRESULT DrawLine::CreateVectex()
{
	//顶点
	VertexLine vertex[] = {
		{200.0f, 100.0f, 1.0f, 1.0f, 0x00ff00ff},
		{200.0f, 200.0f, 1.0f, 1.0f, 0x00ff2255},
		{300.0f, 300.0f, 0.5f, 1.0f, 0x22ff6688},
		{400.0f, 200.0f, 0.5f, 1.0f, 0x00ffffff}
	};

	if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL))) {
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
void DrawLine::Draw()
{
	p_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexLine));
	p_d3dDevice->SetFVF(D3DFVF_VERTEX);
	p_d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 3);
}
