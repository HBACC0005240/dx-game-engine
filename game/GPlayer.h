#pragma once
#include "GWzlData.h"
#include "GWzlOffset.h"
struct POS
{
	int x, y;
};

class GPlayer {

public:
	LPDIRECT3DDEVICE9 p_d3dDevice;
	POS mPos = { 0,0 };
	GWzlData* mpWzl = nullptr;
	GWzlDraw mDraw[8];
	HUM_STATE mState = STAND;
	DIRECTION mDir = UP;
	static int mFrame;
	GTime time;
public:
	GPlayer(GWzlData* _wzl, int x, int y, LPDIRECT3DDEVICE9 d3dDevice);
	~GPlayer();
	void Load(HUM_STATE state, DIRECTION dir);
	void Show();
};