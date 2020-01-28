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

	//加载当前显示图片
	for (int i = 0; i < 8; i++)
	{
		mpWzl->Load(state, dir, i, &mDraw[i]);
	}
}

void GPlayer::Show()
{
	//加载当前显示图片
	if (mDraw[mFrame].data == nullptr){
		mFrame = 0;
	}

	mDraw[mFrame].DrawTexture(p_d3dDevice);
	if (time.CountDown(1000))
	{
		mFrame++;
		if (mFrame >= 8){
			mFrame = 0;
		}
	}
}


