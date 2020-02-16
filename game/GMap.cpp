#include "GMap.h"
#include <unordered_map>
#include "DrawLine.h"

typedef std::unordered_map<int, GWzlDraw*> GDrawMap;
typedef std::pair<int, GWzlDraw*> GDrwa;

//#include "DrawTriangle.h"
GWzlData* Objects[5];
GWzlData* Tiles;
GWzlData* SmTiles;

//大地砖 小地砖 物件
//大地砖缓存容器
GDrawMap g_TilesMap;
//小地砖
GDrawMap g_SmTilesMap;
//物件
GDrawMap g_Objects;

//GWzlDraw* m_Draw;
//GWzlDraw* m_Tiles;
//GWzlDraw* m_SmTiles;
//DrawTriangle* g_san;

DrawLine* g_line;

//当前屏幕中心点坐标
struct POS
{
	float x;
	float y;
};

POS pos;

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

	//线
	g_line = new DrawLine(p_d3dDevice);

	Tiles = nullptr;
	SmTiles = nullptr;

	//m_Draw = new GWzlDraw(p_d3dDevice);

	//m_Tiles = new GWzlDraw();

	//m_SmTiles = new GWzlDraw(p_d3dDevice);

	//g_san = new DrawTriangle(d3dDevice);

	sprintf_s(m_MapFile, ".\\map\\%s.map", file);
}

GMap::~GMap()
{
	delete[] Objects;
	delete Tiles;
	delete SmTiles;

	//delete m_Draw;
	//delete m_Tiles;
	//delete m_SmTiles;
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
	pos.x = pX;
	pos.y = pY;

	//按索引绘制地图
	int map_sort = 0;
	int tiles_sort = 0;
	int sm_tiles_sort = 0;
	int object_sort = 0;
	int width = m_MapHeader.width;
	int height = m_MapHeader.height;
	int file_area = 0;
	int w = 48;
	int h = 32;
	int VIEW = 50;
	//int left	= pX - VIEW < 0 ? 0 : pX - VIEW;
	//int top		= pY - VIEW < 0 ? 0 : pY - VIEW;
	//int right	= pX + VIEW > width ? width : pX + VIEW;
	//int bottom	= pY + VIEW > height ? height : pY + VIEW;
	int left = 0;
	int top = 0;
	int right = width;
	int bottom = height;

	float offsetX = 0;
	float offsetY = 0;
	//GWzlDraw* m_Draw = new GWzlDraw[width * height];
	
#if 0

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

					//初始化一个
					GDrawMap::const_iterator got = g_TilesMap.find(wzx_sort_Tiles);
					if ( got == g_TilesMap.end())
					{
						GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
						Tiles->LoadWzl(wzx_sort_Tiles, tTiles);
						//offsetY = (y * hh - hh);
						//tTiles->DrawTextureRHW(offsetX - tTiles->sImage.x + 400 - ww/2 - (pX * ww), offsetY - tTiles->sImage.y + 300 - hh/2 - (pY * hh));
						tTiles->CreateTexture();
						//GDrwa tDraw(wzx_sort_Tiles, tTiles);
						g_TilesMap.insert(GDrwa(wzx_sort_Tiles, tTiles));
					}
					offsetY = (y * hh - hh);
					offsetX = offsetX - g_TilesMap.at(wzx_sort_Tiles)->sImage.x + 400 - ww / 2 - (pX * ww);
					offsetY = offsetY - g_TilesMap.at(wzx_sort_Tiles)->sImage.y + 300 - hh / 2 - (pY * hh);

					g_TilesMap.at(wzx_sort_Tiles)->Draw(offsetX, offsetY);
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
				//m_SmTiles->DrawTextureRHW(offsetX - m_SmTiles->sImage.x + 400 - 24 - (pX * 48), offsetY - m_SmTiles->sImage.y + 300 - 16 - (pY * 32));
				//m_SmTiles->DrawTextureRHW(offsetX - m_SmTiles->sImage.x + 400 - 24 - (pX * 48), offsetY - m_SmTiles->sImage.y + 300 - 16 - (pY * 32));

				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
			}
		}

	}
#endif // 0
	float oX = 0, oY = 0, oX1 = 0, oY1 = 0;
	for (int x = left; x <= right; x++)
	{
		GetWorldXY(x, 0, oX, oY,true);
		oY1 = oY + m_MapHeader.height * 32.0f;
		g_line->Draw(oX, oY, oX, oY1, 0xff00ffff);
	}

	for (int y = top; y <= bottom; y++)
	{
		GetWorldXY(0, y, oX, oY,true);
		oX1 = oX + +m_MapHeader.width * 48.0f;
		g_line->Draw(oX, oY, oX1, oY, 0xff00ffff);
	}

	for (int x = left; x < right; x++)
	{
		offsetX = x * 48;
		for (int y = top; y < bottom; y++)
		{
			map_sort = x * height + y;
			//位与运算 0&1 = 0 去掉最高位

			//Tiles
			//tiles_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//SmTiles
			//sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (ms_MapInfo[map_sort].wMidImg > 0)
			{
				int i = 0;
			}

			if (object_sort > 0 && true) {
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

				//初始化一个
				GDrawMap::const_iterator objit = g_Objects.find(object_sort);
				if (objit == g_Objects.end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					Objects[file_area]->LoadWzl(object_sort, tTiles);
					tTiles->CreateTexture();
					g_Objects.insert(GDrwa(object_sort, tTiles));
				}
				offsetY = (y * 32 - g_Objects.at(object_sort)->sImage.height);
				offsetX = offsetX - g_Objects.at(object_sort)->sImage.x + 400 - 24 - (pX * 48);
				offsetY = offsetY - g_Objects.at(object_sort)->sImage.y + 300 - 16 - (pY * 32);

				g_Objects.at(object_sort)->Draw(offsetX, offsetY);


				//offsetY = (y * 32 - m_Draw->sImage.height);
				//m_Draw->DrawTextureRHW(offsetX - m_Draw->sImage.x + 400 - 24 - (pX * 48), offsetY - m_Draw->sImage.y + 300 - 16 - (pY * 32));

				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
				//GWzxData wzx(szMapFile);
				//int offset;
				//wzx.GetOffset(wzx_sort, &offset);
			}
		}

	}
	

	//p_d3dDevice->EndScene();
	//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

bool GMap::GetWorldXY(float X, float Y,float& mX,float& mY, bool IsCenter)
{
	//(0,0)=>(24,16) (1,1)=>(72,48)
	mX = X * 48.0f + 400.0f - (pos.x * 48.0f);
	mY = Y * 32.0f + 300.0f - (pos.y * 32.0f);
	if (IsCenter)
	{
		mX = mX - 24.0f;
		mY = mY - 16.0f;
	}

	return true;
}
