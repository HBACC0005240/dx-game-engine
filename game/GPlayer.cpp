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
	if (mState == state && mDir == dir){
		//状态与方向没有改变
		return;
	}
	//清空容器
	m_DrawMap.clear();

	mState = state;
	mDir = dir;

	int totalFarme = TOTAL_FRAME;
	if (state == ATTACK_POS)
	{
		totalFarme = 1;
	}
	//加载当前显示图片
	for (int i = 0; i < totalFarme; i++)
	{
		//GDrawMap::iterator it = m_DrawMap.find(i);
		//if (it == m_DrawMap.end())
		//{
			GWzlDraw* mDraw = new GWzlDraw(p_d3dDevice);
			m_DrawMap.insert(GDrwa(i, mDraw));
	
			mpWzl->Load(state, dir, i, m_DrawMap.at(i), totalFarme);
			if (m_DrawMap.at(i)->data == nullptr)
			{
				//跳过循环
				continue;
			}
		//}

		GWzlDraw* tDraw = m_DrawMap.at(i);
		tDraw->CreateTexture();

		//char file[100];
		//sprintf_s(file, ".\\bmp\\%d.bmp", i);
		//tDraw->SaveBmp(file);
	}
}

void GPlayer::Show()
{
	//加载当前显示图片

	if (m_DrawMap.at(mFrame)->data == nullptr){
		mFrame = 0;
	}

	m_DrawMap.at(mFrame)->Draw(375, 282, COLOR_ARGB);
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
		if (mState == ATTACK_POS){
			//攻击状态就不增加帧数
			return;
		}
		mFrame++;
		if (mFrame >= TOTAL_FRAME){
			mFrame = 0;
		}
	}
}


