#pragma once
#include "GWzlDraw.h"
#include "GWzlData.h"

class GAnimation {

public:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	//文件名称
	char m_wzlFile[100];
	//开始序号
	int m_start = 0;
	//动画张数
	int m_total = 0;
	//当前帧
	int m_farme = 0;
	//计时器
	GTime time;

	//数据对象
	GWzlData* m_pWzl;

	//图片对象
	GWzlDraw* m_pDraw;

	//初始化
	GAnimation(int start_sort,int total, GWzlData* wzlData, LPDIRECT3DDEVICE9 d3dDevice);
	~GAnimation();

	//加载图片
	void Load();

	//绘制
	void Show(int x, int y);
};