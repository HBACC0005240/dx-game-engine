#pragma once
#include "Core.h"
#include "GWzxData.h"
#include "GWzlOffset.h"
#include "GWzlDraw.h"
#include <vector>
//����Wzl����

//Wzlͷ���ṹ
struct WzlHeader {
	char description[44];//www.shandagames.com
	int imageCount;
	int x3[4];
};

class GWzlData {
private:
	char m_WzlFile[100];//�ļ��� .wzl
	GWzxData* pWzx = nullptr;
	LPDIRECT3DDEVICE9 p_d3dDevice;
protected:

public:
	
	GWzlData(char file[]);
	GWzlData();
	~GWzlData();

	//��������
	void Load(HUM_STATE state, DIRECTION dir, int frame, GWzlDraw* pDraw, int totalFrame = 8);
	void LoadWzl(int offset, GWzlDraw* pDraw);
};
