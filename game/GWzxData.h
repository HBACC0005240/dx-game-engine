#pragma once
#include "Core.h"
#include "GWzlOffset.h"

//wzx ͷ���ṹ
struct WzxHeader {
	char description[20]; //www.shandagames.com
	int x1[6];//ռλ
	int imageCount;//ͼƬ����
};

class GWzxData {

private:
	char m_WzxFile[100];	//�ļ�����
	WzxHeader m_WzxHeader;  //ͷ����Ϣ
	int* m_pWzxOffset;		//ƫ�ƻ���
public:
	GWzxData(char file[]);
	~GWzxData();

	void Load();
	int GetOffset(int sort,int* offset);
	int GetOneOffset(HUM_STATE state, DIRECTION dir, int frame, int* offset);
};
