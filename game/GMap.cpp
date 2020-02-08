#include "GMap.h"
//#include "DrawTriangle.h"
GWzlData* Objects[5];
GWzlData* Tiles;
GWzlData* SmTiles;

GWzlDraw* m_Draw;
GWzlDraw* m_Tiles;
GWzlDraw* m_SmTiles;
//DrawTriangle* g_san;

GMap::GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GMap()构造\n");
	p_d3dDevice = d3dDevice;

	//索引对象
	//pWzx = new GWzxData(file);
	for (int i = 0; i < 5; i++)
	{
		Objects[i] = nullptr;
	}

	Tiles = nullptr;
	SmTiles = nullptr;

	m_Draw = new GWzlDraw();

	m_Tiles = new GWzlDraw();

	m_SmTiles = new GWzlDraw();

	//g_san = new DrawTriangle(d3dDevice);

	sprintf_s(m_MapFile, ".\\map\\%s.map", file);
}

GMap::~GMap()
{
	delete[] Objects;
	delete Tiles;
	delete SmTiles;

	delete m_Draw;
	delete m_Tiles;
	delete m_SmTiles;
}

void GMap::Load()
{
	FILE* fp;
	//读取wzx
	fopen_s(&fp, m_MapFile, "r+b");
	if (fp == NULL) {
		OutputDebugString(TEXT("打开文件失败了\n"));
		fclose(fp);
		return;
	}

	//取出wzx头部结构体
	fread(&m_MapHeader, sizeof(MapHeader), 1, fp);

	//偏移头部信息
	fseek(fp, sizeof(MapHeader), SEEK_SET);

	//初始化数据区域大小
	ms_MapInfo = new MapInfo[m_MapHeader.width * m_MapHeader.height];

	//取出图片
	fread(ms_MapInfo, sizeof(MapInfo) * (m_MapHeader.width * m_MapHeader.height), 1, fp);

	fclose(fp);
}



void GMap::Show(int pX, int pY)
{
	//p_d3dDevice->BeginScene();

	//按索引绘制地图
	int map_sort = 0;
	int wzx_sort = 0;
	int wzx_sort_Tiles = 0;
	int wzx_sort_SmTiles = 0;
	int width = m_MapHeader.width;
	int height = m_MapHeader.height;
	int file_area = 0;
	int w = 48;
	int h = 32;
	int VIEW = 10;
	int left	= pX - VIEW < 0 ? 0 : pX - VIEW;
	int top		= pY - VIEW < 0 ? 0 : pY - VIEW;
	int right	= pX + VIEW > width ? width : pX + VIEW;
	int bottom	= pY + VIEW > height ? height : pY + VIEW + 20;

	float offsetX = 0;
	float offsetY = 0;
	//GWzlDraw* m_Draw = new GWzlDraw[width * height];
	

	for (int x = left; x < right; x++)
	{
		offsetX = x * 48;
		for (int y = top; y < bottom; y++)
		{
			map_sort = x * height + y;
			//位与运算 0&1 = 0 去掉最高位
			wzx_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//Tiles
			wzx_sort_Tiles = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			wzx_sort_SmTiles = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (ms_MapInfo[map_sort].wMidImg > 0)
			{
				int i = 0;
			}

			if (wzx_sort_Tiles > 0) {
				if (x%2 == 0 && y%2 ==0 )
				{
					int ww = 48;
					int hh = 32;
					//加载WzxData;
					char szMapFile[100] = ".\\Data\\Tiles";

					//加载WzlData
					if (Tiles == nullptr){
						Tiles = new GWzlData(szMapFile);
					}

					Tiles->LoadWzl(wzx_sort_Tiles, m_Tiles);
					offsetY = (y * hh - hh);
					m_Tiles->DrawTextureRHW(p_d3dDevice, offsetX - m_Tiles->sImage.x + 400 - ww/2 - (pX * ww), offsetY - m_Tiles->sImage.y + 300 - hh/2 - (pY * hh));

					//p_d3dDevice->EndScene();
					//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
					//int i = 0;
				}
			}
		}

	}

	for (int x = left; x < right; x++)
	{
		offsetX = x * 48;
		for (int y = top; y < bottom; y++)
		{
			map_sort = x * height + y;
			//位与运算 0&1 = 0 去掉最高位
			wzx_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//Tiles
			wzx_sort_Tiles = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			wzx_sort_SmTiles = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (ms_MapInfo[map_sort].wMidImg > 0)
			{
				int i = 0;
			}

			if (wzx_sort_SmTiles > 0 && true) {
				//加载WzxData;
				char szMapFile[100] = ".\\Data\\SmTiles";

				//加载WzlData
				if (SmTiles == nullptr) {
					SmTiles = new GWzlData(szMapFile);
				}

				SmTiles->LoadWzl(wzx_sort_SmTiles, m_SmTiles);
				offsetY = (y * 32 - m_SmTiles->sImage.height);
				m_SmTiles->DrawTextureRHW(p_d3dDevice, offsetX - m_SmTiles->sImage.x + 400 - 24 - (pX * 48), offsetY - m_SmTiles->sImage.y + 300 - 16 - (pY * 32));

				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
			}
		}

	}

	for (int x = left; x < right; x++)
	{
		offsetX = x * 48;
		for (int y = top; y < bottom; y++)
		{
			map_sort = x * height + y;
			//位与运算 0&1 = 0 去掉最高位
			wzx_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//Tiles
			wzx_sort_Tiles = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			wzx_sort_SmTiles = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (ms_MapInfo[map_sort].wMidImg > 0)
			{
				int i = 0;
			}

			if (wzx_sort > 0 && true) {
				//加载WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (ms_MapInfo[map_sort].btArea) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", file_area + 1);
				}

				//加载WzlData
				if (Objects[file_area] == nullptr)
				{
					Objects[file_area] = new GWzlData(szMapFile);
				}

				Objects[file_area]->LoadWzl(wzx_sort, m_Draw);
				offsetY = (y * 32 - m_Draw->sImage.height);
				m_Draw->DrawTextureRHW(p_d3dDevice, offsetX - m_Draw->sImage.x + 400 - 24 - (pX * 48), offsetY - m_Draw->sImage.y + 300 - 16 - (pY * 32));

				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
				//GWzxData wzx(szMapFile);
				//int offset;
				//wzx.GetOffset(wzx_sort, &offset);
			}
		}

	}
	//g_san->Draw();
	//p_d3dDevice->EndScene();
	//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
}
