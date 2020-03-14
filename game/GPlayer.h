#pragma once
#include "GWzlData.h"
#include "GWzlOffset.h"
#include <unordered_map>
#include "GMap.h"

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
	POS mPos = { 0,0 }; //人物坐标
	POS nextPos = { 0,0 };//目标的位置
	POS mXY = { 0,0 };//人物xy增量
	POS walk = { 0.05f,0.05f };//xy增量大小
	bool hasMove = false;
	GWzlData* mpWzl = nullptr;
	GDrawMap m_DrawMap;
	HUM_STATE mState = STAND;
	DIRECTION mDir = DOWN;
	static int mFrame;
	GTime time;
	GMap* mMap;
	int mAngle;
	int mLang;
	static BUTTON_KEY L_KEY;
	static BUTTON_KEY R_KEY;
public:
	GPlayer(GWzlData* _wzl, float x, float y, LPDIRECT3DDEVICE9 d3dDevice,GMap* _map);
	~GPlayer();
	void Load();
	void SetDir(int angle, int lang = 1);
	void Show(int frameRate = 150);
	void Move();
};
