#include "GMap.h"


GMap::GMap(char file[], LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"GMap()构造\n");
	p_d3dDevice = d3dDevice;

	//索引对象
	//pWzx = new GWzxData(file);

	sprintf_s(m_MapFile, ".\\map\\%s.map", file);
}

GMap::~GMap()
{

}

void GMap::Load()
{
	FILE* fp;
	//读取wzx
	fopen_s(&fp, m_MapFile, "r+b");
	if (fp == NULL) {
		OutputDebugString(TEXT("打开文件失败了\n"));
		fclose(fp);
		return;
	}

	//取出wzx头部结构体
	fread(&m_MapHeader, sizeof(MapHeader), 1, fp);

	//偏移头部信息
	fseek(fp, sizeof(MapHeader), SEEK_SET);

	//初始化数据区域大小
	ms_MapInfo = new MapInfo[m_MapHeader.width * m_MapHeader.height];

	//取出图片
	fread(ms_MapInfo, sizeof(MapInfo) * (m_MapHeader.width * m_MapHeader.height), 1, fp);

	fclose(fp);
}

void GMap::Show()
{
	//按索引绘制地图
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
			//位与运算 0&1 = 0 去掉最高位
			wzx_sort = (ms_MapInfo[map_sort].wFrImg & 0b0111111111111111);

			if (wzx_sort > 0) {
				//加载WzxData;
				char szMapFile[100] = ".\\Data\\Objects";
				if (ms_MapInfo[map_sort].btArea) {
					sprintf_s(szMapFile, ".\\Data\\Objects%d", ms_MapInfo[map_sort].btArea + 1);
				}

				//加载WzlData
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
