#include "GPlayer.h"
#include "GWzlDraw.h"
int GPlayer::mFrame = 0;

GPlayer::GPlayer(GWzlData* _wzl, int x, int y, LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GPlayer()构造\n");
	mpWzl = _wzl;
	mPos.x = x;
	mPos.y = y;
	p_d3dDevice = d3dDevice;
}

GPlayer::~GPlayer()
{
	OutputDebugString(L"~GPlayer()析构\n");
}

void GPlayer::Load(HUM_STATE state,DIRECTION dir)
{
	int totalFarme = TOTAL_FRAME;
	if (state == BATTLE_POS)
	{
		totalFarme = 1;
	}
	//加载当前显示图片
	for (int i = 0; i < totalFarme; i++)
	{
		GDrawMap::iterator it = m_DrawMap.find(i);
		if (it == m_DrawMap.end())
		{
			GWzlDraw* mDraw = new GWzlDraw(p_d3dDevice);
			m_DrawMap.insert(GDrwa(i, mDraw));
		}
		mpWzl->Load(state, dir, i, m_DrawMap.at(i), totalFarme);
		m_DrawMap.at(i)->CreateTexture();
	}
}

void GPlayer::Show()
{
	//加载当前显示图片
	if (m_DrawMap.at(mFrame)->data == nullptr){
		mFrame = 0;
	}

	m_DrawMap.at(mFrame)->Draw(375, 273, COLOR_ARGB);
	//m_DrawMap.at(mFrame)->Draw(100, 273);
	//m_DrawMap.at(mFrame)->Draw(150, 273);
	//m_DrawMap.at(mFrame)->Draw(200, 273);
	//m_DrawMap.at(mFrame)->Draw(250, 273);
	//m_DrawMap.at(mFrame)->Draw(300, 273);
	//m_DrawMap.at(mFrame)->Draw(350, 273);
	//m_DrawMap.at(mFrame)->Draw(400, 273);
	//m_DrawMap.at(mFrame)->Draw(450, 273);
	//m_DrawMap.at(mFrame)->Draw(500, 273);
	if (time.CountDown(150))
	{
		mFrame++;
		if (mFrame >= TOTAL_FRAME){
			mFrame = 0;
		}
	}
}


