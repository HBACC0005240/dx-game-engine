#include "GWzlDraw.h"



GWzlDraw::GWzlDraw()
{

}

GWzlDraw::~GWzlDraw()
{
	wchar_t buf[50];
	swprintf_s(buf, TEXT("~GWzlDraw()���� data => %p \n"), data);
	OutputDebugString(buf);
	delete data;
}

//�������㻺��
HRESULT GWzlDraw::CreateVectex(LPDIRECT3DDEVICE9 p_d3dDevice)
{
	if (m_d3dBuffer)
	{
		return S_OK;
	}

	GTextureVertex Vertices[] = {
	{  -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
	{  -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
	{  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
	{  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},

	//{ -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
	//{  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
	};


	//�������㻺��
	if (FAILED(p_d3dDevice->CreateVertexBuffer(sizeof(Vertices), 0, GTextureVertex::FVF, D3DPOOL_DEFAULT, &m_d3dBuffer, NULL)))
	{
		return E_FAIL;
	}

	VOID* pVertices;
	if (FAILED(m_d3dBuffer->Lock(0, sizeof(Vertices), &pVertices, 0))) {
		return E_FAIL;
	}
	memcpy(pVertices, Vertices, sizeof(Vertices));
	m_d3dBuffer->Unlock();

	p_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	p_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}



void GWzlDraw::Draw(LPDIRECT3DDEVICE9 d3dDevice)
{
	//OutputDebugString(TEXT("�������\n"));
	///��������
	D3DFORMAT fmt = sImage.pixelFormat == 3 ? D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;
	if (FAILED(d3dDevice->CreateOffscreenPlainSurface(sImage.width, sImage.height, fmt, D3DPOOL_DEFAULT, &m_d3dSurface, NULL))) {
		return;
	}

	//��ȡ������Ϣ
	m_d3dSurface->GetDesc(&m_d3dSurfaceDesc);

	///��������
	D3DLOCKED_RECT lockRect;
	m_d3dSurface->LockRect(&lockRect, 0, 0);

	DWORD* imageData3 = nullptr;
	SHORT* imageData5 = nullptr;

	if (sImage.pixelFormat == 3)
	{
		imageData3 = (DWORD*)lockRect.pBits;
	}
	else if (sImage.pixelFormat == 5)
	{
		imageData5 = (SHORT*)lockRect.pBits;
	}

	for (UINT i = 0; i < m_d3dSurfaceDesc.Height; i++)
	{
		for (UINT j = 0; j < m_d3dSurfaceDesc.Width; j++)
		{
			if (sImage.pixelFormat == 3)
			{
				UINT index = i * lockRect.Pitch / 4 + j;
				UINT sort = ((m_d3dSurfaceDesc.Height - 1) - i) * m_d3dSurfaceDesc.Width + j;
		
				byte  r = m_color[data[sort]].peRed;
				byte  g = m_color[data[sort]].peGreen;
				byte  b = m_color[data[sort]].peBlue;
				if (r != 0 && g != 0 && b != 0)
				{
					imageData3[index] = D3DCOLOR_ARGB(1, r, g, b);
				}
				else {
					imageData3[index] = D3DCOLOR_ARGB(0, 255, 255, 255);
				}
			}
			else if (sImage.pixelFormat == 5)
			{
				//D3DFMT_R5G6B5
				UINT id = (((m_d3dSurfaceDesc.Height - 1) - i) * m_d3dSurfaceDesc.Width + j) * 2;
				BYTE sh1 = data[id];
				BYTE sh2 = data[id + 1];

				USHORT sVal = (sh2 << 8) | sh1;
				UINT index = i * lockRect.Pitch / 2 + j;
				imageData5[index] = sVal;
			}

		}
	}

	m_d3dSurface->UnlockRect();


	IDirect3DSurface9* pBackBuffer = NULL;
	int offsetX = 300 + sImage.x, offsetY = 300 + sImage.y;
	RECT rect1 = { 0,0,m_d3dSurfaceDesc.Width,m_d3dSurfaceDesc.Height };
	RECT rect2 = { offsetX ,offsetY ,m_d3dSurfaceDesc.Width + offsetX,m_d3dSurfaceDesc.Height + offsetY };
	d3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	d3dDevice->StretchRect(m_d3dSurface, &rect1, pBackBuffer, &rect2, D3DTEXF_LINEAR);
}

void GWzlDraw::DrawTexture(LPDIRECT3DDEVICE9 d3dDevice)
{
	CreateVectex(d3dDevice);

	LPD3DXSPRITE pSprite = NULL;
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	HRESULT hr = S_OK;
	hr = D3DXCreateSprite(d3dDevice, &pSprite);

	///������ͼ
	D3DFORMAT fmt = sImage.pixelFormat == 3 ? D3DFMT_X8R8G8B8 : D3DFMT_R5G6B5;
	hr = d3dDevice->CreateTexture(sImage.width, sImage.height, 0, D3DUSAGE_DYNAMIC, fmt, D3DPOOL_DEFAULT, &pTexture, NULL);

	//��ȡ������Ϣ
	pTexture->GetLevelDesc(0,&m_d3dSurfaceDesc);

	///��������
	D3DLOCKED_RECT lockRect;
	pTexture->LockRect(0,&lockRect, 0, 0);

	DWORD* imageData3 = nullptr;
	SHORT* imageData5 = nullptr;

	if (sImage.pixelFormat == 3)
	{
		imageData3 = (DWORD*)lockRect.pBits;
	}
	else if (sImage.pixelFormat == 5)
	{
		imageData5 = (SHORT*)lockRect.pBits;
	}

	for (UINT i = 0; i < m_d3dSurfaceDesc.Height; i++)
	{
		for (UINT j = 0; j < m_d3dSurfaceDesc.Width; j++)
		{
			if (sImage.pixelFormat == 3)
			{
				UINT index = i * lockRect.Pitch / 4 + j;
				UINT sort = ((m_d3dSurfaceDesc.Height - 1) - i) * m_d3dSurfaceDesc.Width + j;

				byte  r = m_color[data[sort]].peRed;
				byte  g = m_color[data[sort]].peGreen;
				byte  b = m_color[data[sort]].peBlue;
				if (r != 0 && g != 0 && b != 0)
				{
					imageData3[index] = D3DCOLOR_XRGB(r, g, b);
				}
				else {
					imageData3[index] = D3DCOLOR_XRGB(255, 255, 255);
				}
			}
			else if (sImage.pixelFormat == 5)
			{
				//D3DFMT_R5G6B5
				UINT id = (((m_d3dSurfaceDesc.Height - 1) - i) * m_d3dSurfaceDesc.Width + j) * 2;
				BYTE sh1 = data[id];
				BYTE sh2 = data[id + 1];

				USHORT sVal = (sh2 << 8) | sh1;
				UINT index = i * lockRect.Pitch / 2 + j;
				imageData5[index] = sVal;
			}

		}
	}
	//����
	pTexture->UnlockRect(0);


	int offsetX = 300 + sImage.x, offsetY = 300 + sImage.y;
	RECT rect1 = { 0,0,m_d3dSurfaceDesc.Width,m_d3dSurfaceDesc.Height };
	//D3DXVECTOR3 pos = D3DXVECTOR3(offsetX, offsetY, 0.0f);

	//pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//pSprite->Draw(pTexture, &rect1, NULL, &pos, 0xffffffff);

	//pSprite->End();

	//pSprite->Release();
	//��λ���������
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	//����
	D3DXMATRIX scale;
	float tWidth = sImage.width * 0.01f * 3.0f;
	float tHeight = sImage.height * 0.01f * 3.0f;
	D3DXMatrixScaling(&scale, tWidth, tHeight, 0.0f);

	//ƽ��
	float tX = sImage.x * 0.01;
	float tY = sImage.y * 0.01;
	D3DXMATRIX Tworld;
	D3DXMatrixTranslation(&Tworld, tX, tY, 0.0f);

	matWorld = scale * Tworld * matWorld;
	d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);


	d3dDevice->SetTexture(0, pTexture);

	d3dDevice->SetStreamSource(0, m_d3dBuffer, 0, sizeof(GTextureVertex));
	d3dDevice->SetFVF(GTextureVertex::FVF);
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}