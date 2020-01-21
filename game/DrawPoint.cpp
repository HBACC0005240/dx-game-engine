#include "DrawPoint.h"

DrawPoint::DrawPoint(Graphics& gfx)
	:
	g_pVB(NULL),
	gfx(gfx)
{
	OutputDebugString(L"DrawPoint()����\n");
}

DrawPoint::~DrawPoint()
{
	OutputDebugString(L"~DrawPoint()����\n");
}

//��ʼ�����㻺��
HRESULT DrawPoint::CreateVectex()
{
	//����
	VertexPoint vertex[] = {
		{100.0f, 100.0f, 0.0f, 1.0f, 0x00ffffff},
		{100.0f, 200.0f, 0.0f, 1.0f, 0x00ffffff},
		{100.0f, 300.0f, 0.0f, 1.0f, 0x00ffffff}
	};

	if (FAILED(gfx.m_d3dDevice->CreateVertexBuffer(sizeof(vertex), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL))) {
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
void DrawPoint::Draw()
{
	gfx.m_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexPoint));
	gfx.m_d3dDevice->SetFVF(D3DFVF_VERTEX);
	gfx.m_d3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, 3);
}
