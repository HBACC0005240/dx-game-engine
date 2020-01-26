#include "GWzlData.h"
#include "zlibwapi.h"
#pragma comment(lib,"zlibwapi.lib")

GWzlData::GWzlData(char file[])
{
	OutputDebugString(L"GWzlData()构造\n");
	//索引对象
	pWzx = new GWzxData(file);

	//图片
	strcpy_s(m_WzlFile, strlen(file) + 1, file);
	strcat_s(m_WzlFile, sizeof(m_WzlFile), ".wzl");
}

GWzlData::~GWzlData()
{
	OutputDebugString(L"~GWzlData()析构\n");
	delete pWzx;
}

void GWzlData::Load(HUM_STATE state, DIRECTION dir,int frame,GWzlDraw * pDraw)
{
	FILE* fp;

	//读取wzl
	fopen_s(&fp, m_WzlFile, "r+b");
	if (fp == NULL) {
		return;
	}

	//根据状态 加载图片
	int offset = 0;
	pWzx->GetOneOffset(state, dir, frame, &offset);
	if (offset == 0)
	{
		return;
	}
	//指向图片结构体头部位置
	fseek(fp, offset, SEEK_SET);

	//读取对应图片头部结构
	fread(&(pDraw->sImage), sizeof(WzlImage), 1, fp);

	//偏移+图片结构体[指针指向数据]
	fseek(fp, offset + sizeof(WzlImage), SEEK_SET);

	//源数据
	BYTE* tBuff = nullptr;
	tBuff = new BYTE[pDraw->sImage.size];
	uLongf inlen = pDraw->sImage.size;

	//读取图片的数据
	fread(tBuff, pDraw->sImage.size, 1, fp);

	//图片实际大小 (5 = 16位图 D3DFMT_R5G6B5[2倍数据大小对齐])(3 = 32位图 D3DFMT_A8R8G8B8)
	int bmpRealSize = pDraw->sImage.width * pDraw->sImage.height * (pDraw->sImage.pixelFormat == 5 ? 2 : 1);

	//使用zlib解压数据
	BYTE* tWzlBuff = new BYTE[bmpRealSize];
	uLong outlen = bmpRealSize;

	//获得位图数据[与调色板对应的位置数据] //这句是，对909 的所有数据进行解压，得到的位图数据
	uncompress(tWzlBuff, &outlen, tBuff, inlen);

	//清除旧数据指针空间
	pDraw->data = tWzlBuff;

	delete[] tBuff;

	fclose(fp);
}

////加载数据
//void GData::GWzlData::Load(HUM_STATE state, DIRECTION dir)
//{
//	FILE* fp;
//	//读取wzl
//	fopen_s(&fp, m_WzlFile, "r+b");
//	if (fp == NULL) {
//		return;
//	}
//
//	//根据状态 加载图片
//	int offset[8] = { 0 };
//	pWzx->GetOffset(state,dir, offset);
//
//	//获取对应索引的图片素材
//	WzlImage image[8] = { 0 };
//	
//	for (int i = 0; i < ARRAYSIZE(offset); i++)
//	{
//		//wchar_t buf[50];
//		//swprintf_s(buf, TEXT("索引：%d \n"), offset[i]);
//		//OutputDebugString(buf);
//		if ( ! offset[i])
//		{
//			continue;
//		}
//
//		WzlImage& tImage = image[i];
//
//		//指向图片结构体头部位置
//		fseek(fp, offset[i], SEEK_SET);
//
//		//读取对应图片头部结构
//		fread(&tImage, sizeof(WzlImage), 1, fp);
//
//		//偏移+图片结构体[指针指向数据]
//		fseek(fp, offset[i] + sizeof(WzlImage) - sizeof(void*), SEEK_SET);
//
//		//源数据
//		BYTE* tBuff = nullptr;
//		tBuff = new BYTE[tImage.size];
//		uLongf inlen = tImage.size;
//
//		//读取图片的数据
//		fread(tBuff, tImage.size, 1, fp);
//
//		//图片实际大小 (5 = 16位图 D3DFMT_R5G6B5[2倍数据大小对齐])(3 = 32位图 D3DFMT_A8R8G8B8)
//		int bmpRealSize = tImage.width * tImage.height * (tImage.pixelFormat == 5 ? 2 : 1);
//
//		//使用zlib解压数据
//		BYTE* tWzlBuff = new BYTE[bmpRealSize];
//		uLong outlen = bmpRealSize;
//
//		//获得位图数据[与调色板对应的位置数据] //这句是，对909 的所有数据进行解压，得到的位图数据
//		uncompress(tWzlBuff, &outlen, tBuff, inlen);
//
//		//清除旧数据指针空间
//		tImage.data = tWzlBuff;
//		delete[] tBuff;
//	}
//
//	fclose(fp);
//}
