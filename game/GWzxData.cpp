#include "GWzxData.h"

GWzxData::GWzxData(char file[])
{
	m_WzxHeader = { 0 };
	m_pWzxOffset = nullptr;
	strcpy_s(m_WzxFile, strlen(file) + 1, file);
	strcat_s(m_WzxFile, sizeof(m_WzxFile), ".wzx");

	//加载
	Load();
}

GWzxData::~GWzxData()
{
	delete[] m_pWzxOffset;
}

//加载所有的索引值
void GWzxData::Load()
{
	FILE* fp;

	//打开
	fopen_s(&fp, m_WzxFile, "r+b");
	if (fp == NULL) {
		return;
	}

	//取出wzx头部结构体
	fread(&m_WzxHeader, sizeof(WzxHeader), 1, fp);

	//偏移头部信息
	fseek(fp, sizeof(WzxHeader), SEEK_SET);
	
	//初始化大小
	m_pWzxOffset = new INT[m_WzxHeader.imageCount];

	//读取
	fread(m_pWzxOffset, sizeof(INT), m_WzxHeader.imageCount, fp);

	//wchar_t buf[50] = { 0 };
	//for (int i = 0; i < m_WzxHeader.imageCount; i++)
	//{
	//	swprintf_s(buf, TEXT("[%d]:%d \n"), i, m_pWzxOffset[i]);
	//	OutputDebugString(buf);
	//}

	fclose(fp);
}


//获取索引值
int GWzxData::GetAllOffset(HUM_STATE state, DIRECTION dir,int* offset)
{
	int start = state + (dir * 8);
	for (int i = 0; i < 8; i++)
	{
		offset[i] = m_pWzxOffset[start + i];
		if (offset[i] == 48)
		{
			offset[i] = 0;
		}
	}
	return 0;
}

//获取索引值
int GWzxData::GetOneOffset(HUM_STATE state, DIRECTION dir, int frame, int* offset)
{
	int start = state + (dir * 8);
	*offset = m_pWzxOffset[start + frame];
	if (*offset == 48)
	{
		*offset = 0;
	}
	return 0;
}


