#include "GMap.h"
#include <unordered_map>
#include "DrawLine.h"
#include "GAnimation.h"
#include "GPlayer.h"
#include "DrawGText.h"

#define WND_WIDTH 800
#define WND_HEIGHT 600

typedef std::unordered_map<int, GWzlDraw*> GDrawMap;
typedef std::pair<int, GWzlDraw*> GDrwa;

typedef std::unordered_map<int, GAnimation*> GAniMap;
typedef std::pair<int, GAnimation*> GAni;

//��Դ�����
GWzlData* Tiles;//���ש
GWzlData* SmTiles;//С��ש
GWzlData* Objects[6];//���
GWzlData* pWzlHum;//������Դ
GPlayer* g_player;//����
DrawLine* g_line;//������
DrawGText* g_text;//���ֶ���

//��������
GDrawMap g_TilesMap;//���ש
GDrawMap g_SmTilesMap;//С��ש
GDrawMap g_Objects[6];//���
GDrawMap g_MaskObjects[6];//�������
GAniMap g_Animation;//����

//������Ϣ
POS pos = { 323 ,283 };//��������
POS map = { 48.0f,32.0f };//��ͼС������Ϣ
//�ǲ�
static float bu = pos.x;
HUM_STATE state = STAND;
DIRECTION dir = DOWN;

bool keyF = false, keyFF = true;
bool keyG = false, keyGG = true;
bool keyH = false, keyHH = true;
bool keyJ = false, keyJJ = true;
bool keyK = false, keyKK = true;

GMap::GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice, LPD3DXFONT d3dFont)
{
	OutputDebugString(L"GMap()����\n");
	p_d3dDevice = d3dDevice;
	p_d3dFont = d3dFont;
	//��������
	//pWzx = new GWzxData(file);
	for (int i = 0; i < 5; i++)
	{
		Objects[i] = nullptr;
	}
	sprintf_s(m_MapFile, ".\\map\\%s.map", file);

	//��
	g_line = new DrawLine(p_d3dDevice);
	//��ʼ��������
	g_text = new DrawGText(p_d3dFont);

	Tiles = nullptr;
	SmTiles = nullptr;

	//��������ͼƬ
	char humfile[] = ".\\Data\\hum2";
	//char file[] = ".\\Data\\hum2";
	//char file[] = ".\\Data\\hum3";
	//char file[] = ".\\Data\\items";
	pWzlHum = new GWzlData(humfile);
	g_player = new GPlayer(pWzlHum, 0, 0, p_d3dDevice);
}

GMap::~GMap()
{
	delete Tiles;
	delete SmTiles;
	delete[] Objects;
	delete pWzlHum;
	delete g_player;
	delete g_line;
	//delete m_Draw;
	//delete m_Tiles;
	//delete m_SmTiles;
}

void GMap::Load()
{
	//�����ʼ��״̬
	g_player->Load(STAND, DOWN);

	FILE* fp;
	//��ȡwzx
	fopen_s(&fp, m_MapFile, "r+b");
	if (fp == NULL) {
		OutputDebugString(TEXT("���ļ�ʧ����\n"));
		fclose(fp);
		return;
	}

	//ȡ��wzxͷ���ṹ��
	fread(&m_MapHeader, sizeof(MapHeader), 1, fp);

	//ƫ��ͷ����Ϣ
	fseek(fp, sizeof(MapHeader), SEEK_SET);

	//��ʼ�����������С
	ms_MapInfo = new MapInfo[m_MapHeader.width * m_MapHeader.height];

	//ȡ��ͼƬ
	fread(ms_MapInfo, sizeof(MapInfo) * (m_MapHeader.width * m_MapHeader.height), 1, fp);

	fclose(fp);
}



void GMap::Show(int pX, int pY)
{
	//p_d3dDevice->BeginScene();
	//pos.x = pX;
	//pos.y = pY;

	pX = static_cast<int>(pos.x);
	pY = static_cast<int>(pos.y);

	//���������Ƶ�ͼ
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

	//��һ���
	GMap::GoXY();

	g_player->Show();

	//��������
	wchar_t buf[50] = { 0 };
	wsprintf(buf, L"xy��[%d,%d]", static_cast<int>(pos.x), static_cast<int>(pos.y));
	g_text->Draw(buf, 380, 300, 800, 600, 0xffffffff);

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
	mX = X * map.x + 400.0f - (pos.x * map.x) - map.x/2;
	mY = Y * map.y + 300.0f - (pos.y * map.y) - map.y/2;
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
			//λ������ 0&1 = 0 ȥ�����λ

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

			//�ļ��� +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (tiles_sort >= 0 && (x % 2 == 0 && y % 2 == 0)) {

				//����WzxData;
				char szMapFile[100] = ".\\Data\\Tiles";

				//����WzlData
				if (Tiles == nullptr) {
					Tiles = new GWzlData(szMapFile);
				}

				//��ʼ��һ��
				GDrawMap::const_iterator tilesit = g_TilesMap.find(tiles_sort);
				if (tilesit == g_TilesMap.end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					Tiles->LoadWzl(tiles_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//��������ѭ��
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
			//λ������ 0&1 = 0 ȥ�����λ

			//Tiles
			//tiles_sort = (ms_MapInfo[map_sort].wBkImg & 0b0111111111111111) - 1;
			//SmTiles
			sm_tiles_sort = (ms_MapInfo[map_sort].wMidImg & 0b0111111111111111) - 1;

			//object
			//object_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111) - 1;

			//�ļ��� +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (sm_tiles_sort > 0) {

				//����WzxData;
				char szMapFile[100] = ".\\Data\\SmTiles";

				//����WzlData
				if (SmTiles == nullptr) {
					SmTiles = new GWzlData(szMapFile);
				}

				//��ʼ��һ��
				GDrawMap::const_iterator Smtilesit = g_SmTilesMap.find(sm_tiles_sort);
				if (Smtilesit == g_SmTilesMap.end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					SmTiles->LoadWzl(sm_tiles_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//��������ѭ��
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
			//λ������ 0&1 = 0 ȥ�����λ

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

			//light [�Ƴ�ԭ��ͼ���Ǹ��ƾɵĵ�]
			int light = (ms_MapInfo[map_sort].btAniFrame);

			//�ļ��� +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (object_sort > 0 && light == 0) {
				//����WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (ms_MapInfo[map_sort].btArea) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", file_area + 1);
				}

				//����WzlData
				if (Objects[file_area] == nullptr)
				{
					Objects[file_area] = new GWzlData(szMapFile);
				}

				//��ʼ��һ��
				GDrawMap::const_iterator objit = g_Objects[file_area].find(object_sort);
				if (objit == g_Objects[file_area].end())
				{
					GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
					Objects[file_area]->LoadWzl(object_sort, tTiles);
					if (tTiles->data == nullptr)
					{
						//��������ѭ��
						delete tTiles;
						continue;
					}

					//����ļ�
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

			//light [�Ƴ�ԭ��ͼ���Ǹ��ƾɵĵ�]
			int light = (ms_MapInfo[map_sort].btAniFrame);

			//�ļ��� +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (object_sort > 0) {

				//��ȡobject��ͼƬ����
				GDrawMap::const_iterator objit = g_Objects[file_area].find(object_sort);
				if (objit == g_Objects[file_area].end()) {
					//û�ҵ��ö���
					continue;
				}

				//��ȡ��ǰͼƬ
				GWzlDraw* tObject = g_Objects[file_area].at(object_sort);

				//���㵱ǰ������Y����
				int PosHeight = (y - pos.y) * map.y;
				if (tObject->sImage.height > PosHeight) {

					//��ʼ��һ��
					GDrawMap::const_iterator objit = g_MaskObjects[file_area].find(object_sort);
					if (objit == g_MaskObjects[file_area].end())
					{
						GWzlDraw* tTiles = new GWzlDraw(p_d3dDevice);
						Objects[file_area]->LoadWzl(object_sort, tTiles);
						if (tTiles->data == nullptr)
						{
							//��������ѭ��
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
			//λ������ 0&1 = 0 ȥ�����λ

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

			//�ļ��� +1
			file_area = ms_MapInfo[map_sort].btArea;

			if (light_sort > 0 && object_sort > 0) {
				//����WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (file_area) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", file_area + 1);
				}

				//����WzlData
				if (Objects[file_area] == nullptr)
				{
					Objects[file_area] = new GWzlData(szMapFile);
				}

				//��ʼ��һ��
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

//��ͼ ���ݸ������꣬����ʵ�ʻ������Ͻ�����
bool GMap::GetMapWorldXY(GWzlDraw* GDraw, float X, float Y, float& mX, float& mY)
{
	//mx = ��Ļƫ�� + ����ͼx * ���ӿ�ȣ� - ������x * ���ӿ�ȣ� - �����ӿ��/2��- ͼ��ƫ��x
	mX = 400.0f + (X * map.x) - (pos.x * map.x) - (map.x / 2) - GDraw->sImage.x;
	mY = 300.0f + (Y * map.y) - (pos.y * map.y) - (map.y / 2) - GDraw->sImage.y - GDraw->sImage.height;
	return true;
}

bool GMap::keyMouse(int x, int y, BUTTON_KEY bk)
{
	int px = x - WND_WIDTH/2;
	int py = y - WND_HEIGHT/2;

	//������(��֪y/x��Ƕ�) ����(��֪�Ƕ���y/x)
	double rad = std::atan2(py, px);
	int angle = 180 * rad / PI;//������ת�Ƕ�
	
	wchar_t buf[50] = { 0 };
	//swprintf_s(buf, TEXT("���꣺%d,%d;[%d]\n"), px, px, angle);
	//OutputDebugString(buf);

	switch (bk)
	{
	case L_BUTTON_DOWN:
		dir = HasDir(angle);
		g_player->Load(WALK, dir);
		swprintf_s(buf, TEXT("������£�%d,%d;\t�Ƕ�:%d��;����:\t%d\n"), x, y, angle, dir);
		break;
	case L_BUTTON_UP:
		//swprintf_s(buf, TEXT("�������%d,%d\n"), x, y);
		break;
	case R_BUTTON_DOWN:
		//swprintf_s(buf, TEXT("�Ҽ����£�%d,%d\n"), x, y);
		break;
	case R_BUTTON_UP:
		//swprintf_s(buf, TEXT("�Ҽ�����%d,%d\n"), x, y);
		break;
	default:
		break;
	}

	OutputDebugString(buf);
	return false;
}

DIRECTION GMap::HasDir(int angle)
{
	state = WALK;

	if (angle >= -112.5 && angle < -67.5){
		return UP;
	}
	else if (angle >= -67.5 && angle < -22.5){
		return RIGHT_UP;
	}
	else if (angle >= -22.5 && angle < 22.5){
		return RIGHT;
	}
	else if (angle >= 22.5 && angle < 67.5){
		return RIGHT_DOWN;
	}
	else if (angle >= 67.5 && angle < 112.5){
		return DOWN;
	}
	else if (angle >= 112.5 && angle < 157.5){
		return LEFT_DOWN;
	}
	else if ((angle >= 157.5 && angle <= 179) || (angle >= -179 && angle < -157.5)){
		return LEFT;
	}else if (angle >= -157.5 && angle <= -112.5) {
		return LEFT_UP;
	}
	return DOWN;
}

void GMap::GoXY()
{
	if ( ! time.CountDown(50)) {
		return;
	}

	switch (state)
	{
	case STAND:
		break;
	case WALK:
		pos.x += 0.07f;
		if (abs(pos.x - bu) >= 1) {
			bu = pos.x;
			state = STAND;
			g_player->Load(state, dir);
		}

		break;
	case RUN:
		break;
	case ATTACK_POS:
		break;
	case ATTACK:
		break;
	case ATTACK2:
		break;
	case ATTACK3:
		break;
	case SPELLS:
		break;
	case DIG_MEAT:
		break;
	case INJURED:
		break;
	case DEATH:
		break;
	default:
		break;
	}
}

bool GMap::KeyBoard(char key, BUTTON_KEY bk)
{
	wchar_t buf[50] = { 0 };
	switch (bk)
	{
	case KB_DOWN:
		swprintf_s(buf, TEXT("���£�%c\n"), key);
		break;
	case KB_UP:
		swprintf_s(buf, TEXT("����%c\n"), key);
		break;
	default:
		break;
	}
	OutputDebugString(buf);
	return false;
}