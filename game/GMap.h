#pragma once
#include "Core.h"
#include "GWzlData.h"
#include "GWzlDraw.h"


struct MapHeader {
	short width;	//��ͼ��
	short height;	//��ͼ��
	char title[16];
	int updatetime[2];
	char Reserved[24];
};

struct MapInfo {
	unsigned short wBkImg;	//��һ��
	unsigned short wMidImg; //�ڶ���
	unsigned short wFrImg;	//������
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
	char m_MapFile[100];	//�ļ�����
	MapHeader m_MapHeader;
	MapInfo* ms_MapInfo;
	std::vector<GWzlDraw*> g_Draw;
public:
	GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice);
	~GMap();
	void Load();
	void Show(int x,int y);
};