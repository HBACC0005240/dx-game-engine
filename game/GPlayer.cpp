#include "GPlayer.h"
#include "GWzlDraw.h"
int GPlayer::mFrame = 0;

GPlayer::GPlayer(GWzlData* _wzl, float x, float y, LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GPlayer()构造\n");
	mpWzl = _wzl;
	nextPos = mPos = { x,y };

	p_d3dDevice = d3dDevice;
}

GPlayer::~GPlayer()
{
	OutputDebugString(L"~GPlayer()析构\n");
}

void GPlayer::Load()
{
	//清空容器
	m_DrawMap.clear();
	//帧数重置
	mFrame = 0;

	int totalFarme = TOTAL_FRAME;
	if (mState == ATTACK_POS)
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
	
			mpWzl->Load(mState, mDir, i, m_DrawMap.at(i), totalFarme);
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


void GPlayer::Move()
{
	switch (mState)
	{
	case STAND:
		Show(150);
		return;
	case WALK:
		Show(50);
		break;
	case RUN:
		Show(90);
		break;
	case ATTACK_POS:
		break;
	case ATTACK:
		break;
	case ATTACK2:
		break;
	case ATTACK3:
		break;
	case SPELLS:
		break;
	case DIG_MEAT:
		break;
	case INJURED:
		break;
	case DEATH:
		break;
	default:
		break;
	}

	if (nextPos.x > mPos.x){
		if (mXY.x > nextPos.x - mPos.x)
		{
			mXY.x = nextPos.x - mPos.x;
		}
		mPos.x += mXY.x;
	}else if (nextPos.x < mPos.x) {
		//100 < 102
		//100 < 101.55
		//100 < 100.04 
		//-0.05 < -0.04;
		if (mXY.x < nextPos.x - mPos.x)
		{
			mXY.x = nextPos.x - mPos.x;
		}
		mPos.x += mXY.x;
	}else {
		mPos.x = static_cast<int>(mPos.x);
		mXY.x = 0;
	}

	if (nextPos.y > mPos.y) {
		if (mXY.y > nextPos.y - mPos.y)
		{
			mXY.y = nextPos.y - mPos.y;
		}
		mPos.y += mXY.y;
	}else if (nextPos.y < mPos.y) {
		if (mXY.y < nextPos.y - mPos.y)
		{
			mXY.y = nextPos.y - mPos.y;
		}
		mPos.y += mXY.y;
	}else {
		mPos.y = static_cast<int>(mPos.y);
		mXY.y = 0;
	}


	if (mXY.x == 0 && mXY.y == 0){
		mState = STAND;
		Load();
	}

	//if (abs(nextPos.y - mPos.y) > 0) {
	//	mPos.y += mXY.y;
	//}
	//else {
	//	mState = STAND;
	//	mXY = { mXY.x,0 };
	//}
	
	

}

const int lang = 2;
void GPlayer::SetDir(int angle)
{
	if (nextPos.x != mPos.x || nextPos.y != mPos.y){
		return;
	}
	nextPos = mPos;

	if (angle >= -112.5 && angle < -67.5) {
		mDir = UP;
		mXY.x = 0;
		mXY.y = walk.y * -1;
		nextPos.y -= lang;
	}
	else if (angle >= -67.5 && angle < -22.5) {
		mDir = RIGHT_UP;
		mXY.x = walk.x;
		mXY.y = walk.y * -1;
		nextPos.x += lang;
		nextPos.y -= lang;
	}
	else if (angle >= -22.5 && angle < 22.5) {
		mDir = RIGHT;
		mXY.x = walk.x;
		mXY.y = 0;

		nextPos.x += lang;
	}
	else if (angle >= 22.5 && angle < 67.5) {
		mDir = RIGHT_DOWN;
		mXY.x = walk.x;
		mXY.y = walk.y;
		nextPos.x += lang;
		nextPos.y += lang;
	}
	else if (angle >= 67.5 && angle < 112.5) {
		mDir = DOWN;
		mXY.x = 0;
		mXY.y = walk.y;

		nextPos.y += lang;
	}
	else if (angle >= 112.5 && angle < 157.5) {
		mDir = LEFT_DOWN;
		mXY.x = walk.x * -1;
		mXY.y = walk.y;

		nextPos.x -= lang;
		nextPos.y += lang;
	}
	else if ((angle >= 157.5 && angle <= 179) || (angle >= -179 && angle < -157.5)) {
		mDir = LEFT;
		mXY.x = walk.x * -1;
		mXY.y = 0;

		nextPos.x -= lang;
	}
	else if (angle >= -157.5 && angle <= -112.5) {
		mDir = LEFT_UP;
		mXY.x = walk.x * -1;
		mXY.y = walk.y * -1;

		nextPos.x -= lang;
		nextPos.y -= lang;
	}

	wchar_t buf[50] = { 0 };
	swprintf_s(buf, TEXT("当前：%0.2f,%0.2f;\t方向:%d;\t目标:%0.2f,%0.2f;\n"), mPos.x, mPos.y, mDir, nextPos.x, nextPos.y);
	OutputDebugString(buf);

	//加载动画
	Load();
}

void GPlayer::Show(int frameRate)
{
	//加载当前显示图片
	if (m_DrawMap.at(mFrame)->data == nullptr){
		mFrame = 0;
	}

	m_DrawMap.at(mFrame)->Draw(375, 282, COLOR_ARGB);
	if (time.CountDown(frameRate))
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


