#pragma once
#include "Core.h"
#include "GWzlData.h"
#include "GWzlDraw.h"


struct MapHeader {
	short width;	//地图宽
	short height;	//地图高
	char title[16];
	int updatetime[2];
	char Reserved[24];
};

struct MapInfo {
	unsigned short wBkImg;	//第一层
	unsigned short wMidImg; //第二层
	unsigned short wFrImg;	//第三层
	byte btDoorIndex;		
	byte btDoorOffset;
	byte btAniFrame;
	byte btAniTick;
	byte btArea;
	byte btLight;
};

const double PI = 3.1415927;

class GMap {
	
public:
	LPDIRECT3DDEVICE9 p_d3dDevice;
	LPD3DXFONT p_d3dFont = nullptr;//文字对象
	char m_MapFile[100];	//文件名字
	MapHeader m_MapHeader;
	MapInfo* ms_MapInfo;
	std::vector<GWzlDraw*> g_Draw;
	RECT rect;
	GTime time;
public:
	GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice, LPD3DXFONT d3dFont);
	~GMap();
	void Load();
	void Show(int x,int y);
	//返回世界坐标系中心点实际坐标
	static bool GetWorldXY(float X, float Y, float& mX, float& mY,bool IsCenter = false);
	static bool GetMapWorldXY(GWzlDraw* GDraw, float X, float Y, float& mX, float& mY);
	static bool GetLightWorldXY(float X, float Y, float& mX, float& mY);
	void DrawTiles();
	void DrawSmTiles();
	void DrawObjects();
	void DrawPlayer();
	void DrawAnimation();
	void DrawWorldLine();

	void BtnState();
	static bool KeyBoard(char key, BUTTON_KEY bk);
	static bool keyMouse(int x, int y, BUTTON_KEY bk);

	bool CheckMap(int x,int y);
};