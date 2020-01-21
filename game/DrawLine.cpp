#include "DrawLine.h"

DrawLine::DrawLine(Graphics& gfx)
	:
	g_pVB(NULL),
	gfx(gfx)
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
	VertexLine vertex[] = {
		{200.0f, 100.0f, 0.0f, 1.0f, 0x00ffffff},
		{200.0f, 200.0f, 0.0f, 1.0f, 0x00ffffff},
		{300.0f, 300.0f, 0.0f, 1.0f, 0x00ffffff},
		{400.0f, 200.0f, 0.0f, 1.0f, 0x00ffffff}
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
void DrawLine::Draw()
{
	gfx.m_d3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(VertexLine));
	gfx.m_d3dDevice->SetFVF(D3DFVF_VERTEX);
	gfx.m_d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 3);
}
