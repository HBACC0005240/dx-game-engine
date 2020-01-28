#include "DrawLine.h"

DrawLine::DrawLine(LPDIRECT3DDEVICE9 d3dDevice)
	:
	g_pVB(NULL),
	p_d3dDevice(d3dDevice)
{
	OutputDebugString(L"DrawLine()����\n");
}

DrawLine::~DrawLine()
{
	OutputDebugString(L"~DrawLine()����\n");
}

//��ʼ�����㻺��
HRESULT DrawLine::CreateVectex()
{
	//����
	DWORD color1 = 0xffffffff;
	DWORD color2 = 0xff00ff00;
	VertexLine vertex[] = {
		{-100.0f, 0.0f, 0.0f,  color1},
		{ 100.0f, 0.0f, 0.0f,  color1},
		{ 0.0f,  100.0f, 0.0f, color2},
		{ 0.0f, -100.0f, 0.0f, color2}
	};

	if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL))) {
		return E_FAIL;
	}
	//throw AHLIN::Exception(_FILE, _LINE, L"����point���㻺��ʧ��");

	void* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertex), &pVertices, 0))) {
		return E_FAIL;
	}

	memcpy(pVertices, vertex, sizeof(vertex));

	g_pVB->Unlock();

	return S_OK;
}

//���Ƶ��б�
void DrawLine::Draw()
{
	p_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexLine));
	p_d3dDevice->SetFVF(D3DFVF_VERTEX);
	p_d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 3);
}
