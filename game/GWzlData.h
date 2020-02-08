#pragma once
#include "Core.h"
#include "GWzxData.h"
#include "GWzlOffset.h"
#include "GWzlDraw.h"
#include <vector>
//加载Wzl数据

//Wzl头部结构
struct WzlHeader {
	char description[44];//www.shandagames.com
	int imageCount;
	int x3[4];
};

class GWzlData {
private:
	char m_WzlFile[100];//文件名 .wzl
	GWzxData* pWzx = nullptr;
	LPDIRECT3DDEVICE9 p_d3dDevice;
protected:

public:
	
	GWzlData(char file[]);
	GWzlData();
	~GWzlData();

	//加载数据
	void Load(HUM_STATE state, DIRECTION dir, int frame, GWzlDraw* pDraw, int totalFrame = 8);
	void LoadWzl(int offset, GWzlDraw* pDraw);
};
