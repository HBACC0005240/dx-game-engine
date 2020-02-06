#pragma once
#include "Core.h"
#include "GWzlOffset.h"

//wzx 头部结构
struct WzxHeader {
	char description[20]; //www.shandagames.com
	int x1[6];//占位
	int imageCount;//图片数量
};

class GWzxData {

private:
	char m_WzxFile[100];	//文件名字
	WzxHeader m_WzxHeader;  //头部信息
	int* m_pWzxOffset;		//偏移缓存
public:
	GWzxData(char file[]);
	~GWzxData();

	void Load();
	int GetOffset(int sort,int* offset);
	int GetOneOffset(HUM_STATE state, DIRECTION dir, int frame, int* offset);
};
