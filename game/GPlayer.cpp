#include "GPlayer.h"
#include "GWzlDraw.h"
int GPlayer::mFrame = 0;

GPlayer::GPlayer(GWzlData* _wzl, int x, int y, LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GPlayer()����\n");
	mpWzl = _wzl;
	mPos.x = x;
	mPos.y = y;
	p_d3dDevice = d3dDevice;
}

GPlayer::~GPlayer()
{
	OutputDebugString(L"~GPlayer()����\n");
}

void GPlayer::Load(HUM_STATE state,DIRECTION dir)
{
	if (mState == state && mDir == dir){
		//״̬�뷽��û�иı�
		return;
	}
	//�������
	m_DrawMap.clear();

	mState = state;
	mDir = dir;

	int totalFarme = TOTAL_FRAME;
	if (state == ATTACK_POS)
	{
		totalFarme = 1;
	}
	//���ص�ǰ��ʾͼƬ
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
				//����ѭ��
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
	//���ص�ǰ��ʾͼƬ

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
			//����״̬�Ͳ�����֡��
			return;
		}
		mFrame++;
		if (mFrame >= TOTAL_FRAME){
			mFrame = 0;
		}
	}
}


