#pragma once
#include "GWzlData.h"
#include "GWzlOffset.h"
#include <unordered_map>

struct POS
{
	float x, y;
};

typedef std::unordered_map<int, GWzlDraw*> GDrawMap;
typedef std::pair<int, GWzlDraw*> GDrwa;

#define TOTAL_FRAME 8
class GPlayer {

public:
	LPDIRECT3DDEVICE9 p_d3dDevice;
	POS mPos = { 0,0 };
	GWzlData* mpWzl = nullptr;
	GDrawMap m_DrawMap;
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