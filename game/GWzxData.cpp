#include "GWzxData.h"

GWzxData::GWzxData(char file[])
{
	m_WzxHeader = { 0 };
	m_pWzxOffset = nullptr;
	strcpy_s(m_WzxFile, strlen(file) + 1, file);
	strcat_s(m_WzxFile, sizeof(m_WzxFile), ".wzx");

	//����
	Load();
}

GWzxData::~GWzxData()
{
	delete[] m_pWzxOffset;
}

//�������е�����ֵ
void GWzxData::Load()
{
	FILE* fp;

	//��
	fopen_s(&fp, m_WzxFile, "r+b");
	if (fp == NULL) {
		return;
	}

	//ȡ��wzxͷ���ṹ��
	fread(&m_WzxHeader, sizeof(WzxHeader), 1, fp);

	//ƫ��ͷ����Ϣ
	fseek(fp, sizeof(WzxHeader), SEEK_SET);
	
	//��ʼ����С
	m_pWzxOffset = new INT[m_WzxHeader.imageCount];

	//��ȡ
	fread(m_pWzxOffset, sizeof(INT), m_WzxHeader.imageCount, fp);

	//wchar_t buf[50] = { 0 };
	//for (int i = 0; i < m_WzxHeader.imageCount; i++)
	//{
	//	swprintf_s(buf, TEXT("[%d]:%d \n"), i, m_pWzxOffset[i]);
	//	OutputDebugString(buf);
	//}

	fclose(fp);
}


//��ȡ����ֵ
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

//��ȡ����ֵ
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


