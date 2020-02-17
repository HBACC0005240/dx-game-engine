#pragma once
#include "GWzlDraw.h"
#include "GWzlData.h"

class GAnimation {

public:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	//�ļ�����
	char m_wzlFile[100];
	//��ʼ���
	int m_start = 0;
	//��������
	int m_total = 0;
	//��ǰ֡
	int m_farme = 0;
	//��ʱ��
	GTime time;

	//���ݶ���
	GWzlData* m_pWzl;

	//ͼƬ����
	GWzlDraw* m_pDraw;

	//��ʼ��
	GAnimation(int start_sort,int total, GWzlData* wzlData, LPDIRECT3DDEVICE9 d3dDevice);
	~GAnimation();

	//����ͼƬ
	void Load();

	//����
	void Show(int x, int y);
};