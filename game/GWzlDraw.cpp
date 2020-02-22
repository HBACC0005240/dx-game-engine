#include "GWzlDraw.h"

RGBQUAD GWzlDraw::aColors[256] = { 0 };

GWzlDraw::GWzlDraw(LPDIRECT3DDEVICE9 p_d3dDevice)
{
	m_d3dDevice = p_d3dDevice;
	data = nullptr;
	m_d3dBuffer = nullptr;
}

GWzlDraw::GWzlDraw()
{
	data = nullptr;
	m_d3dBuffer = nullptr;
}

GWzlDraw::~GWzlDraw()
{
	wchar_t buf[50];
	swprintf_s(buf, TEXT("~GWzlDraw()析构 data => %p \n"), data);
	OutputDebugString(buf);
	delete data;
}

//创建顶点缓存
float bei = 1.42f;
HRESULT GWzlDraw::CreateVectex(LPDIRECT3DDEVICE9 p_d3dDevice)
{
	if (m_d3dBuffer)
	{
		return S_OK;
	}

	float tWidth = sImage.width / 100.0f * bei;
	float tHeight = sImage.height / 100.0f * bei;

	float wof2 = -0.35f + (sImage.x / 100.0f * bei);
	float hof2 = 1.6f + (sImage.y / 100.0f * bei);

	tWidth = tWidth + wof2;
	tHeight = (tHeight - hof2) * -1.0f;

	GTextureVertex Vertices[] = {
	//{  -0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
	//{  -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
	//{  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
	//{  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
	{  wof2,  tHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
	{  wof2,  hof2, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
	{  tWidth,  tHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
	{  tWidth,  hof2, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},

	//{ -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
	//{  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
	};


	//创建顶点缓存
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

//创建顶点缓存
float bei2 = 1.0f;
HRESULT GWzlDraw::CreateVectexRHW(int x, int y)
{
	if (m_d3dBuffer)
	{
		m_d3dBuffer->Release();
		//return S_OK;
	}

	float tWidth = sImage.width * bei2;
	float tHeight = sImage.height * bei2;

	//D3D9 顶点缓存误差  x=0 实际上是从 -0.5 开始 多了第一行第一列
	float wof2 = x + sImage.x - 0.5f;
	float hof2 = y + sImage.y - 0.5f;

	tWidth = tWidth + wof2;
	tHeight = tHeight + hof2;

	GTextureVertexRHW Vertices[] = {
		{  wof2 ,  tHeight, 0.0f, 1.0f,0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
		{  wof2,   hof2, 0.0f, 1.0f,0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
		{  tWidth,  tHeight, 0.0f, 1.0f,0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
		{  tWidth,  hof2, 0.0f, 1.0f,0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
	};


	//创建顶点缓存
	if (FAILED(m_d3dDevice->CreateVertexBuffer(sizeof(Vertices), 0, GTextureVertexRHW::FVF, D3DPOOL_DEFAULT, &m_d3dBuffer, NULL)))
	{
		return E_FAIL;
	}

	VOID* pVertices;
	if (FAILED(m_d3dBuffer->Lock(0, sizeof(Vertices), &pVertices, 0))) {
		return E_FAIL;
	}
	memcpy(pVertices, Vertices, sizeof(Vertices));
	m_d3dBuffer->Unlock();

	return S_OK;
}

//创建顶点缓存
HRESULT GWzlDraw::CreateVectexRHW2(int x, int y)
{
	if (m_d3dBuffer)
	{
		m_d3dBuffer->Release();
		//return S_OK;
	}

	float tWidth = sImage.width;
	float tHeight = sImage.height;

	//D3D9 顶点缓存误差  x=0 实际上是从 -0.5 开始 多了第一行第一列
	float wof2 = x + sImage.x - 0.5f;
	float hof2 = y + sImage.y - 0.5f;
	
	tWidth = tWidth + wof2;
	tHeight = tHeight + hof2;

	GTextureVertexRHW2 Vertices[] = {
		{  wof2 ,   tHeight, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f},
		{  wof2,    hof2,	 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f},
		{  tWidth,  tHeight, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f},
		{  tWidth,  hof2,	 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f},
	};

	//创建顶点缓存
	if (FAILED(m_d3dDevice->CreateVertexBuffer(sizeof(Vertices), 0, GTextureVertexRHW2::FVF, D3DPOOL_DEFAULT, &m_d3dBuffer, NULL)))
	{
		return E_FAIL;
	}

	VOID* pVertices;
	if (FAILED(m_d3dBuffer->Lock(0, sizeof(Vertices), &pVertices, 0))) {
		return E_FAIL;
	}
	memcpy(pVertices, Vertices, sizeof(Vertices));
	m_d3dBuffer->Unlock();

	return S_OK;
}


void GWzlDraw::Draw(int x,int y,WZL_ALPHA mode)
{
	if (m_pTexture == nullptr){
		return;
	}
	//平移矩阵
	//D3DXMATRIX sXYZ;
	//D3DXMatrixTranslation(&sXYZ, 10, 1, 1);
	//m_d3dDevice->SetTransform(D3DTS_WORLD, &sXYZ);
	CreateVectexRHW2(x, y);

	//设置贴图	
	m_d3dDevice->SetTexture(0, m_pTexture);


	if (mode == COLOR_ARGB)
	{
		//绘制前要开启融合运算
		m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//设定融合因子，采用默认值
		m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else if (mode == COLOR_LIGHT)
	{		
		//绘制前要开启融合运算
		m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//高光效果
		m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else {
		m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	m_d3dDevice->SetStreamSource(0, m_d3dBuffer, 0, sizeof(GTextureVertexRHW2));
	m_d3dDevice->SetFVF(GTextureVertexRHW2::FVF);
	m_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void GWzlDraw::DrawTexture(LPDIRECT3DDEVICE9 d3dDevice)
{
	CreateVectex(d3dDevice);

	LPD3DXSPRITE pSprite = NULL;
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	IDirect3DSurface9* m_d3dSurface = nullptr;
	D3DSURFACE_DESC m_d3dSurfaceDesc = {};

	HRESULT hr = S_OK;
	hr = D3DXCreateSprite(d3dDevice, &pSprite);

	///创建贴图
	D3DFORMAT fmt = sImage.pixelFormat == 3 ? D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;
	hr = d3dDevice->CreateTexture(sImage.width, sImage.height, 0, D3DUSAGE_DYNAMIC, fmt, D3DPOOL_DEFAULT, &pTexture, NULL);

	//获取表面信息
	pTexture->GetLevelDesc(0,&m_d3dSurfaceDesc);

	///表面数据
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

				byte  r = m_color[data[sort]].rgbRed;
				byte  g = m_color[data[sort]].rgbGreen;
				byte  b = m_color[data[sort]].rgbBlue;
				if (r != 0 && g != 0 && b != 0)
				{
					imageData3[index] = D3DCOLOR_ARGB(0xff,r, g, b);
				}
				else {
					imageData3[index] = D3DCOLOR_ARGB(0,0,0,0);
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
	//解锁
	pTexture->UnlockRect(0);


	int offsetX = 300 + sImage.x, offsetY = 300 + sImage.y;
	RECT rect1 = { 0,0,static_cast<LONG>(m_d3dSurfaceDesc.Width),static_cast<LONG>(m_d3dSurfaceDesc.Height) };
	//D3DXVECTOR3 pos = D3DXVECTOR3(offsetX, offsetY, 0.0f);

	//pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//pSprite->Draw(pTexture, &rect1, NULL, &pos, 0xffffffff);

	//pSprite->End();

	//pSprite->Release();
	//单位化世界矩阵
	//D3DXMATRIX matWorld;
	//D3DXMatrixIdentity(&matWorld);

	////缩放
	//D3DXMATRIX scale;
	//float bei = 1.6f;
	//float tWidth = sImage.width / 100.0f * bei;
	//float tHeight = sImage.height / 100.0f * bei;
	//D3DXMatrixScaling(&scale, tWidth, tHeight, 0.0f);

	////平移
	//float pyX = -0.55f,pyY = 0.2f;
	//float tX = (sImage.x / 100.0f * bei) + pyX;
	//float tY = (sImage.y / 100.0f * bei) + pyY;
	//D3DXMATRIX Tworld;
	//D3DXMatrixTranslation(&Tworld, tX, tY, 0.0f);

	//matWorld = scale * Tworld * matWorld;
	//d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	d3dDevice->SetTexture(0, pTexture);

	//绘制前要开启融合运算
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//设定融合因子，采用默认值
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	d3dDevice->SetStreamSource(0, m_d3dBuffer, 0, sizeof(GTextureVertex));
	d3dDevice->SetFVF(GTextureVertex::FVF);
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	if (pTexture != NULL)
	{
		pTexture->Release();
	}
}


void GWzlDraw::CreateTexture()
{

	if (data == nullptr)
	{
		return;
	}
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	//LPDIRECT3DSURFACE9 m_d3dSurface = nullptr;
	D3DSURFACE_DESC m_d3dSurfaceDesc = {};

	HRESULT hr = S_OK;

	///创建贴图
	D3DFORMAT fmt = sImage.pixelFormat == 3 ? D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;
	hr = m_d3dDevice->CreateTexture(sImage.width, sImage.height, 0, D3DUSAGE_DYNAMIC, fmt, D3DPOOL_DEFAULT, &pTexture, NULL);

	//获取表面信息
	pTexture->GetLevelDesc(0, &m_d3dSurfaceDesc);

	///表面数据
	D3DLOCKED_RECT lockRect;
	pTexture->LockRect(0, &lockRect, 0, 0);

	int sort = 0;
	int index = 0;
	int height = m_d3dSurfaceDesc.Height;
	int width = m_d3dSurfaceDesc.Width;

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

	//获取调色板
	//OpenRGB();

	for (UINT h = 0; h < height; h++)
	{
		for (UINT w = 0; w < width; w++)
		{
			if (sImage.pixelFormat == 3) {
				//数据 第一行 是图片的最后一行 数据从上往下读取
				//D3DFMT_A8R8G8B8
				sort = (h * width) + w;
				BYTE  r = p_color[data[sort]].peRed;
				BYTE  g = p_color[data[sort]].peGreen;
				BYTE  b = p_color[data[sort]].peBlue;
				//BYTE  r = aColors[data[sort]].rgbRed;
				//BYTE  g = aColors[data[sort]].rgbGreen;
				//BYTE  b = aColors[data[sort]].rgbBlue;
				DWORD color = D3DCOLOR_ARGB(0xff, r, g, b);
				//index = (height - h) * width + w;

				//图片数组 绘制从下往上
				UINT index = (height - 1 - h) * lockRect.Pitch / 4 + w;
				if (color != 0xff000000)
				{
					imageData3[index] = D3DCOLOR_ARGB(0xff,r, g, b);
				}
				else {
					imageData3[index] = D3DCOLOR_ARGB(0,0, 0, 0);
				}
			}
			else if (sImage.pixelFormat == 5)
			{
				//D3DFMT_R5G6B5
				sort = ((h * width) + w) * 2;
				BYTE sh1 = data[sort];
				BYTE sh2 = data[sort + 1];
				USHORT sVal = (sh2 << 8) | sh1;

				index = (height - 1 - h) * lockRect.Pitch / 2 + w;
				imageData5[index] = sVal;
			}
		}
	}
		
	//解锁
	pTexture->UnlockRect(0);

	//-------------------------------------
	if (sImage.pixelFormat == 5) {

		LPDIRECT3DTEXTURE9 dstTexture = NULL;

		//新建一个D3DFMT_A8R8G8B8
		IDirect3DSurface9* m_srcD3dSurface;
		IDirect3DSurface9* m_dstD3dSurface;

		hr = m_d3dDevice->CreateTexture(sImage.width, sImage.height, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &dstTexture, NULL);
		dstTexture->GetSurfaceLevel(0,&m_dstD3dSurface);
		pTexture->GetSurfaceLevel(0, &m_srcD3dSurface);

		D3DXLoadSurfaceFromSurface(
			m_dstD3dSurface, 
			NULL, NULL, 
			m_srcD3dSurface, 
			NULL, NULL, 
			D3DX_FILTER_LINEAR, 
			D3DCOLOR_ARGB(0,0,0,0)
		);
		D3DSURFACE_DESC d3ddesc;
		m_dstD3dSurface->GetDesc(&d3ddesc);

		///表面数据
		D3DLOCKED_RECT lockr = {0};
		m_dstD3dSurface->LockRect(&lockr, 0, 0);
		DWORD* imageData33 = (DWORD*)lockr.pBits;

		DWORD color = 0;
		for (UINT i = 0; i < d3ddesc.Height; i++)
		{
			for (UINT j = 0; j < d3ddesc.Width; j++)
			{
				UINT index = i * lockr.Pitch / 4 + j;
				if (imageData33[index] == 0xff000000)
				{
					imageData33[index] = D3DCOLOR_ARGB(0, 0, 0, 0);
				}
			}
		}

		m_dstD3dSurface->UnlockRect();

		m_pTexture = dstTexture;
	}
	else {
		m_pTexture = pTexture;
	}
}

void GWzlDraw::OpenRGB() {

	if (aColors[1].rgbRed != 0){
		return;
	}
	FILE* fp;
	//读取调色板
	fopen_s(&fp, "RGBQUAD.dat", "r+b");
	fread(&aColors, sizeof(aColors), 1, fp);
	fclose(fp);
}

struct 	BitMapLine
{
	BYTE colorIndex;
};

void GWzlDraw::OpenSaveBmp()
{
	FILE *fp;

	fopen_s(&fp, "1.bmp", "r+b");

	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	RGBQUAD aColors[256] = {0};


	//头部结构
	fread(&head, sizeof(BITMAPFILEHEADER), 1, fp);

	//图片结构
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	fread(&info, sizeof(BITMAPINFOHEADER), 1, fp);


	//调色板
	fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);
	fread(&aColors, sizeof(aColors), 1, fp);

	//图片数据
	BitMapLine* lines = nullptr;
	lines = new BitMapLine[info.biSizeImage];

	//读取数据
	fseek(fp, head.bfOffBits, SEEK_SET);
	fread(lines, info.biSizeImage, 1, fp);

	fclose(fp);

	//写出文件

	fopen_s(&fp, "RGBQUAD.dat", "wb");

	//BITMAPFILEHEADER bitHeader = { 0x4d42,54 + sizeof(RGBQUAD) * 256,0,0,1078 };
	//BITMAPINFOHEADER bitInfo = { 40,info.biWidth,info.biHeight,1,8,0,info.biSizeImage,0,0,256,0 };

	BITMAPFILEHEADER header;
	header.bfType = 0x4D42;
	header.bfSize = head.bfSize;
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = head.bfOffBits;

	BITMAPINFOHEADER tinfo;
	tinfo.biSize = sizeof(BITMAPINFOHEADER);
	tinfo.biWidth = info.biWidth;
	tinfo.biHeight = info.biHeight;
	tinfo.biPlanes = 1;
	tinfo.biBitCount = 8;
	tinfo.biCompression = 0;
	tinfo.biSizeImage = info.biSizeImage;
	tinfo.biXPelsPerMeter = 0;
	tinfo.biYPelsPerMeter = 0;
	tinfo.biClrUsed = 256;
	tinfo.biClrImportant = 0;

	//fwrite(&header, sizeof(BITMAPFILEHEADER), 1, fp);
	//fwrite(&tinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(&aColors, sizeof(aColors), 1, fp); 
	//fwrite(lines, info.biSizeImage, 1, fp);
	
	fclose(fp);
}

void GWzlDraw::SaveBmp(char file[],int biWidth,int biHeight, int bmpDataSize, BYTE *bmpData)
{
	FILE* fp;
	RGBQUAD tColors[256] = { 0 };

	//读取调色板
	fopen_s(&fp, "RGBQUAD.dat", "r+b");
	fread(&tColors, sizeof(tColors), 1, fp);
	fclose(fp);

	//写出文件
	fopen_s(&fp, file, "wb");

	BITMAPFILEHEADER header;
	header.bfType = 0x4D42;
	header.bfSize = bmpDataSize + 1078;//图片总大小(头部+数据)
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = 1078;//整个图片数据的偏移(头部+图结构+调色板)

	BITMAPINFOHEADER tinfo;
	tinfo.biSize = sizeof(BITMAPINFOHEADER);
	tinfo.biWidth = biWidth;//图片宽度
	tinfo.biHeight = biHeight;//图片高度
	tinfo.biPlanes = 1;
	tinfo.biBitCount = 8;
	tinfo.biCompression = 0;
	tinfo.biSizeImage = bmpDataSize;
	tinfo.biXPelsPerMeter = 0;
	tinfo.biYPelsPerMeter = 0;
	tinfo.biClrUsed = 256;
	tinfo.biClrImportant = 0;

	fwrite(&header, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&tinfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(&tColors, sizeof(tColors), 1, fp);
	fwrite(bmpData, bmpDataSize, 1, fp);

	fclose(fp);
}
