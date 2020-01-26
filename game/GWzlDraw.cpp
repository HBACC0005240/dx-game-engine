#include "GWzlDraw.h"

GWzlDraw::GWzlDraw()
{

}

GWzlDraw::~GWzlDraw()
{
	wchar_t buf[50];
	swprintf_s(buf, TEXT("~GWzlDraw()析构 data => %p \n"), data);
	OutputDebugString(buf);
	delete data;
}

void GWzlDraw::Draw(LPDIRECT3DDEVICE9 d3dDevice)
{
	//OutputDebugString(TEXT("绘制完成\n"));
	///创建表面
	D3DFORMAT fmt = sImage.pixelFormat == 3 ? D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;
	if (FAILED(d3dDevice->CreateOffscreenPlainSurface(sImage.width, sImage.height, fmt, D3DPOOL_DEFAULT, &m_d3dSurface, NULL))) {
		return;
	}

	//获取表面信息
	m_d3dSurface->GetDesc(&m_d3dSurfaceDesc);

	///表面数据
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
