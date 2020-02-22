#include "GAnimation.h"

GAnimation::GAnimation(int start_sort, int total, GWzlData* wzlData, LPDIRECT3DDEVICE9 d3dDevice)
{
	m_start = start_sort;
	m_total = total;
	m_d3dDevice = d3dDevice;

	//数据对象
	m_pWzl = wzlData;

	//初始化总大小图形对象
	m_pDraw = new GWzlDraw[m_total];
}

GAnimation::~GAnimation()
{
	delete m_pWzl;
	delete[] m_pDraw;
}

void GAnimation::Load()
{
	//获取total张图片
	for (int i = 0; i < m_total; i++)
	{
		m_pDraw[i].m_d3dDevice = m_d3dDevice;

		m_pWzl->LoadWzl(m_start + i,&m_pDraw[i]);
		if (m_pDraw[i].data == nullptr){
			continue;
		}
		m_pDraw[i].CreateTexture();
	}
}

void GAnimation::Show(int x,int y)
{
	//加载当前显示图片
	if (m_pDraw[m_farme].data == nullptr) {
		m_farme = 0;
	}

	m_pDraw[m_farme].Draw(x, y,COLOR_LIGHT);

	if (time.CountDown(150))
	{
		m_farme++;
		if (m_farme >= m_total) {
			m_farme = 0;
		}
	}
}
