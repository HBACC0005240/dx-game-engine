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

class GMap {

public:
	LPDIRECT3DDEVICE9 p_d3dDevice;
	char m_MapFile[100];	//文件名字
	MapHeader m_MapHeader;
	MapInfo* ms_MapInfo;
	std::vector<GWzlDraw*> g_Draw;
public:
	GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice);
	~GMap();
	void Load();
	void Show(int x,int y);
};