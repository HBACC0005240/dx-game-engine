#include "GMap.h"
#include <unordered_map>
#include "DrawLine.h"
#include "GAnimation.h"
#include "GPlayer.h"

typedef std::unordered_map<int, GWzlDraw*> GDrawMap;
typedef std::pair<int, GWzlDraw*> GDrwa;

typedef std::unordered_map<int, GAnimation*> GAniMap;
typedef std::pair<int, GAnimation*> GAni;

//#include "DrawTriangle.h"
GWzlData* Objects[6];
GWzlData* Tiles;
GWzlData* SmTiles;



//大地砖 小地砖 物件
//大地砖缓存容器
GDrawMap g_TilesMap;
//小地砖
GDrawMap g_SmTilesMap;
//物件
GDrawMap g_Objects[6];
//遮罩物件
GDrawMap g_MaskObjects[6];

//灯泡
GAniMap g_Animation;

//人物资源
GWzlData* pWzlHum;
//人物
GPlayer* g_player;
//GWzlDraw* m_Draw;
//GWzlDraw* m_Tiles;
//GWzlDraw* m_SmTiles;
//DrawTriangle* g_san;

DrawLine* g_line;

//当前屏幕中心点坐标
//struct POS
//{
//	float x;
//	float y;
//};

POS pos;
POS map = { 48.0f,32.0f };

bool keyF = false, keyFF = true;
bool keyG = false, keyGG = true;
bool keyH = false, keyHH = true;
bool keyJ = false, keyJJ = true;
bool keyK = false, keyKK = true;

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
	sprintf_s(m_MapFile, ".\\map\\%s.map", file);

	//线
	g_line = new DrawLine(p_d3dDevice);

	Tiles = nullptr;
	SmTiles = nullptr;

	//加载人物图片
	char humfile[] = ".\\Data\\hum2";
	//char file[] = ".\\Data\\hum2";
	//char file[] = ".\\Data\\hum3";
	//char file[] = ".\\Data\\items";
	pWzlHum = new GWzlData(humfile);
	g_player = new GPlayer(pWzlHum, 0, 0, p_d3dDevice);
}

GMap::~GMap()
{
	delete[] Objects;
	delete Tiles;
	delete SmTiles;
	delete pWzlHum;
	delete g_player;
	//delete m_Draw;
	//delete m_Tiles;
	//delete m_SmTiles;
}

void GMap::Load()
{
	//人物初始化
	g_player->Load(WALK, UP);

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
	int width = m_MapHeader.width;
	int height = m_MapHeader.height;
	int VIEW = 20;
	int left	= pX - VIEW < 0 ? 0 : pX - VIEW;
	int top		= pY - VIEW < 0 ? 0 : pY - VIEW;
	int right	= pX + VIEW > width ? width : pX + VIEW;
	int bottom	= pY + VIEW > height ? height : pY + VIEW + 20;

	rect = { left,top,right,bottom };
	//line
	if (keyKK)
	{
		DrawWorldLine();
	}

	//Tiles
	if (keyFF)
	{
		DrawTiles();
	}

	//SmTiles
	if (keyGG)
	{
		DrawSmTiles();
	}



	//Objects
	if (keyHH)
	{
		DrawObjects();
	}

	g_line->Draw(400.0f, 284.0f, 400.0f, 316.0f, 0xffffffff);
	g_line->Draw(376.0f, 300.0f, 424.0f, 300.0f, 0xffffffff);

	//玩家绘制
	g_player->Show();

	if (keyHH)
	{
		//player-mask
		DrawPlayer();
	}
	//light
	if (keyJJ)
	{
		DrawAnimation();
	}


	//F
	if (::GetAsyncKeyState(0x46) & 0x8000f) {
		if (keyF)
		{
			keyFF = keyFF ? false : true;
			keyF = false;
		}
	}
	else {
		keyF = true;
	}

	//G
	if (::GetAsyncKeyState(0x47) & 0x8000f) {
		if (keyG)
		{
			keyGG = keyGG ? false : true;
			keyG = false;
		}
	}
	else {
		keyG = true;
	}

	//H
	if (::GetAsyncKeyState(0x48) & 0x8000f) {
		if (keyH)
		{
			keyHH = keyHH ? false : true;
			keyH = false;
		}
		
	}
	else {
		keyH = true;
	}
	
	//J
	if (::GetAsyncKeyState(0x4A) & 0x8000f) {
		if (keyJ)
		{
			keyJJ = keyJJ ? false : true;
			keyJ = false;
		}
	}
	else {
		keyJ = true;
	}

	//K
	if (::GetAsyncKeyState(0x4B) & 0x8000f) {
		if (keyK)
		{
			keyKK = keyKK ? false : true;
			keyK = false;
		}
	}
	else {
		keyK = true;
	}
}


bool GMap::GetLightWorldXY(float X, float Y, float& mX, float& mY)
{
	//(0,0)=>(24,16) (1,1)=>(72,48)
	mX = X * 48.0f + 400.0f - (pos.x * 48.0f) - 24.0f;
	mY = Y * 32.0f + 300.0f - (pos.y * 32.0f) - 16.0f;
	return true;
}

void GMap::DrawTiles()
{
	//Tiles
	float offsetX = 0, offsetY = 0;
	int map_sort = 0;
	int tiles_sort = 0;
	int file_area = 0;

	for (int x = rect.left; x < rect.right; x++)
	{
		for (int y = rect.top; y < rect.bottom; y++)
		{
			map_sort = x * m_MapHeader.height + y;
			//位与运算 0&1 = 0 去掉最高位

			if (x == 362 && y == 247)
			{
				int i = 0;
			}

			//Tiles
			tiles_sort = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			//sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			//object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (tiles_sort >= 0 && (x % 2 == 0 && y % 2 == 0)) {

				//加载WzxData;
				char szMapFile[100] = ".\\Data\\Tiles";

				//加载WzlData
				if (Tiles == nullptr) {
					Tiles = new GWzlData(szMapFile);
				}

				//初始化一个
				GDrawMap::const_iterator tilesit = g_TilesMap.find(tiles_sort);
				if (tilesit == g_TilesMap.end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					Tiles->LoadWzl(tiles_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//跳过本次循环
						delete tTiles;
						continue;
					}
					tTiles->CreateTexture();
					g_TilesMap.insert(GDrwa(tiles_sort, tTiles));
				}
				GWzlDraw* tObject = g_TilesMap.at(tiles_sort);
				GetMapWorldXY(tObject, x, y + 2, offsetX, offsetY);
				tObject->Draw(offsetX, offsetY,COLOR_ARGB);
			}
		}

	}
}

void GMap::DrawSmTiles()
{
	//SmTiles
	float offsetX = 0, offsetY = 0;
	int map_sort = 0;
	int sm_tiles_sort = 0;
	int file_area = 0;

	for (int x = rect.left; x < rect.right; x++)
	{
		for (int y = rect.top; y < rect.bottom; y++)
		{
			map_sort = x * m_MapHeader.height + y;
			//位与运算 0&1 = 0 去掉最高位

			//Tiles
			//tiles_sort = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			//object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (sm_tiles_sort > 0) {

				//加载WzxData;
				char szMapFile[100] = ".\\Data\\SmTiles";

				//加载WzlData
				if (SmTiles == nullptr) {
					SmTiles = new GWzlData(szMapFile);
				}

				//初始化一个
				GDrawMap::const_iterator Smtilesit = g_SmTilesMap.find(sm_tiles_sort);
				if (Smtilesit == g_SmTilesMap.end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					SmTiles->LoadWzl(sm_tiles_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//跳过本次循环
						delete tTiles;
						continue;
					}
					tTiles->CreateTexture();
					g_SmTilesMap.insert(GDrwa(sm_tiles_sort, tTiles));
				}
				GWzlDraw* tObject = g_SmTilesMap.at(sm_tiles_sort);

				GetMapWorldXY(tObject, x, y, offsetX, offsetY);
				tObject->Draw(offsetX, offsetY,COLOR_ARGB);
				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;

			}
		}
	}
}

void GMap::DrawObjects()
{
	//Objects
	float offsetX = 0, offsetY = 0;
	int map_sort = 0;
	int object_sort = 0;
	int file_area = 0;
	

	for (int x = rect.left; x < rect.right; x++)
	{
		for (int y = rect.top; y < rect.bottom; y++)
		{
			map_sort = x * m_MapHeader.height + y;
			//位与运算 0&1 = 0 去掉最高位

			if (x == 338 && y == 254)
			{
				int i = 0;
			}

			//Tiles
			//tiles_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//SmTiles
			//sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//light [移除原地图上那个破旧的灯]
			int light = (ms_MapInfo[map_sort].btAniFrame);

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (object_sort > 0 && light == 0) {
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
				GDrawMap::const_iterator objit = g_Objects[file_area].find(object_sort);
				if (objit == g_Objects[file_area].end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					Objects[file_area]->LoadWzl(object_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//跳过本次循环
						delete tTiles;
						continue;
					}

					//输出文件
					//char file[100] = ".\\Bmp\\0.bmp";
					//sprintf_s(file, ".\\Bmp\\%d.bmp", object_sort);
					//tTiles->SaveBmp(file, tTiles->sImage.width, tTiles->sImage.height, tTiles->sImage.width * tTiles->sImage.height, tTiles->data);
					tTiles->CreateTexture();
					g_Objects[file_area].insert(GDrwa(object_sort, tTiles));
				}
				GWzlDraw* tObject = g_Objects[file_area].at(object_sort);
				GetMapWorldXY(tObject, x, y + 1, offsetX, offsetY);
				
				tObject->Draw(offsetX, offsetY, COLOR_ARGB);
				
				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
			}
		}
	}
}

void GMap::DrawPlayer()
{
	//Objects
	float offsetX = 0, offsetY = 0;
	int map_sort = 0;
	int object_sort = 0;
	int file_area = 0;

	for (int x = pos.x; x < pos.x + 2; x++)
	{
		for (int y = pos.y + 1; y < rect.bottom; y++)
		{
			map_sort = x * m_MapHeader.height + y;

			//object
			object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//light [移除原地图上那个破旧的灯]
			int light = (ms_MapInfo[map_sort].btAniFrame);

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (object_sort > 0) {

				//获取object的图片对象
				GDrawMap::const_iterator objit = g_Objects[file_area].find(object_sort);
				if (objit == g_Objects[file_area].end()) {
					//没找到该对象
					continue;
				}

				//获取当前图片
				GWzlDraw* tObject = g_Objects[file_area].at(object_sort);

				//计算当前与人物Y距离
				int PosHeight = (y - pos.y) * map.y;
				if (tObject->sImage.height > PosHeight) {

					//初始化一个
					GDrawMap::const_iterator objit = g_MaskObjects[file_area].find(object_sort);
					if (objit == g_MaskObjects[file_area].end())
					{
						GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
						Objects[file_area]->LoadWzl(object_sort, tTiles);
						if (tTiles->data == nullptr)
						{
							//跳过本次循环
							delete tTiles;
							continue;
						}
						tTiles->CreateTexture(0x99);
						g_MaskObjects[file_area].insert(GDrwa(object_sort, tTiles));
					}
					GWzlDraw* tObject = g_MaskObjects[file_area].at(object_sort);
					GetMapWorldXY(tObject, x, y + 1, offsetX, offsetY);
					tObject->Draw(offsetX, offsetY, COLOR_ARGB);
					//p_d3dDevice->EndScene();
					//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
					//int i = 0;
				}
			}
		}
	}
}

void GMap::DrawAnimation()
{
	//Objects
	float offsetX = 0, offsetY = 0;
	int map_sort = 0;
	int light_sort = 0;
	int object_sort = 0;
	int file_area = 0;

	for (int x = rect.left; x < rect.right; x++)
	{
		offsetX = x * 48;
		for (int y = rect.top; y < rect.bottom; y++)
		{
			map_sort = x * m_MapHeader.height + y;
			//位与运算 0&1 = 0 去掉最高位

			if (x == 338 && y == 254)
			{
				int i = 0;
			}

			//Tiles
			//tiles_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//SmTiles
			//sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;
			//aniFrame
			light_sort = (ms_MapInfo[map_sort].btAniFrame);

			//文件号 +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (light_sort > 0 && object_sort > 0) {
				//加载WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (file_area) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", file_area + 1);
				}

				//加载WzlData
				if (Objects[file_area] == nullptr)
				{
					Objects[file_area] = new GWzlData(szMapFile);
				}

				//初始化一个
				GAniMap::const_iterator lightit = g_Animation.find(object_sort);
				if (lightit == g_Animation.end())
				{
					GAnimation *tAni = new GAnimation(object_sort, 10, Objects[file_area], p_d3dDevice);
					tAni->Load();
					g_Animation.insert(GAni(object_sort, tAni));
				}
				GAnimation* tObject = g_Animation.at(object_sort);
				GetLightWorldXY(x, y - 2, offsetX, offsetY);
				tObject->Show(offsetX, offsetY);
				//p_d3dDevice->EndScene();
				//p_d3dDevice->Present(NULL, NULL, NULL, NULL);
				//int i = 0;
			}
		}

	}
}

void GMap::DrawWorldLine() {
	float oX = 0, oY = 0, oX1 = 0, oY1 = 0;
	for (int x = rect.left; x <= rect.right; x++)
	{
		GetWorldXY(x, 0, oX, oY, true);
		oY1 = oY + m_MapHeader.height * map.y;
		g_line->Draw(oX, oY, oX, oY1, 0xff00ffff);
	}

	for (int y = rect.top; y <= rect.bottom; y++)
	{
		GetWorldXY(0, y, oX, oY, true);
		oX1 = oX + m_MapHeader.width * map.x;
		g_line->Draw(oX, oY, oX1, oY, 0xff00ffff);
	}
}


bool GMap::GetWorldXY(float X, float Y, float& mX, float& mY, bool IsCenter)
{
	//(0,0)=>(24,16) (1,1)=>(72,48)
	mX = X * map.x + 400.0f - (pos.x * map.x);
	mY = Y * map.y + 300.0f - (pos.y * map.y);
	if (IsCenter)
	{
		mX = mX - map.x / 2;
		mY = mY - map.y / 2;
	}

	return true;
}

//绘图 传递格子坐标，返回实际绘制左上角坐标
bool GMap::GetMapWorldXY(GWzlDraw* GDraw, float X, float Y, float& mX, float& mY)
{
	//mx = 屏幕偏移 + （地图x * 格子宽度） - （人物x * 格子宽度） - （格子宽度/2）- 图像偏移x
	mX = 400.0f + (X * map.x) - (pos.x * map.x) - (map.x / 2) - GDraw->sImage.x;
	mY = 300.0f + (Y * map.y) - (pos.y * map.y) - (map.y / 2) - GDraw->sImage.y - GDraw->sImage.height;
	return true;
}