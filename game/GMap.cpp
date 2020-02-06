#include "GMap.h"


GMap::GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GMap()����\n");
	p_d3dDevice = d3dDevice;

	//��������
	//pWzx = new GWzxData(file);

	sprintf_s(m_MapFile, ".\\map\\%s.map", file);
}

GMap::~GMap()
{

}

void GMap::Load()
{
	FILE* fp;
	//��ȡwzx
	fopen_s(&fp, m_MapFile, "r+b");
	if (fp == NULL) {
		OutputDebugString(TEXT("���ļ�ʧ����\n"));
		fclose(fp);
		return;
	}

	//ȡ��wzxͷ���ṹ��
	fread(&m_MapHeader, sizeof(MapHeader), 1, fp);

	//ƫ��ͷ����Ϣ
	fseek(fp, sizeof(MapHeader), SEEK_SET);

	//��ʼ�����������С
	ms_MapInfo = new MapInfo[m_MapHeader.width * m_MapHeader.height];

	//ȡ��ͼƬ
	fread(ms_MapInfo, sizeof(MapInfo) * (m_MapHeader.width * m_MapHeader.height), 1, fp);

	fclose(fp);
}

void GMap::Show()
{
	//���������Ƶ�ͼ
	int map_sort = 0;
	int wzx_sort = 0;
	int width = m_MapHeader.width;
	int height = m_MapHeader.height;
	
	//GWzlDraw* m_Draw = new GWzlDraw[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			map_sort = x * height + y;
			//λ������ 0&1 = 0 ȥ�����λ
			wzx_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111);

			if (wzx_sort > 0) {
				//����WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (ms_MapInfo[map_sort].btArea) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", ms_MapInfo[map_sort].btArea + 1);
				}

				//����WzlData
				GWzlData wzl(szMapFile);
				GWzlDraw m_Draw;
				wzl.LoadWzl(wzx_sort, &m_Draw);
				m_Draw.DrawTextureRHW(p_d3dDevice,x*48,y*32);
				
				//GWzxData wzx(szMapFile);
				//int offset;
				//wzx.GetOffset(wzx_sort, &offset);
			}
		}
		break;
	}
}
