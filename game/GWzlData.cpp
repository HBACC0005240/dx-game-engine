#include "GWzlData.h"
#include "zlibwapi.h"
#pragma comment(lib,"zlibwapi.lib")

GWzlData::GWzlData(char file[])
{
	OutputDebugString(L"GWzlData()����\n");
	//��������
	pWzx = new GWzxData(file);

	//ͼƬ
	strcpy_s(m_WzlFile, strlen(file) + 1, file);
	strcat_s(m_WzlFile, sizeof(m_WzlFile), ".wzl");
}

GWzlData::~GWzlData()
{
	OutputDebugString(L"~GWzlData()����\n");
	delete pWzx;
}

void GWzlData::Load(HUM_STATE state, DIRECTION dir,int frame,GWzlDraw * pDraw)
{
	FILE* fp;

	//��ȡwzl
	fopen_s(&fp, m_WzlFile, "r+b");
	if (fp == NULL) {
		return;
	}

	//����״̬ ����ͼƬ
	int offset = 0;
	pWzx->GetOneOffset(state, dir, frame, &offset);
	if (offset == 0)
	{
		return;
	}
	//ָ��ͼƬ�ṹ��ͷ��λ��
	fseek(fp, offset, SEEK_SET);

	//��ȡ��ӦͼƬͷ���ṹ
	fread(&(pDraw->sImage), sizeof(WzlImage), 1, fp);

	//ƫ��+ͼƬ�ṹ��[ָ��ָ������]
	fseek(fp, offset + sizeof(WzlImage), SEEK_SET);

	//Դ����
	BYTE* tBuff = nullptr;
	tBuff = new BYTE[pDraw->sImage.size];
	uLongf inlen = pDraw->sImage.size;

	//��ȡͼƬ������
	fread(tBuff, pDraw->sImage.size, 1, fp);

	//ͼƬʵ�ʴ�С (5 = 16λͼ D3DFMT_R5G6B5[2�����ݴ�С����])(3 = 32λͼ D3DFMT_A8R8G8B8)
	int bmpRealSize = pDraw->sImage.width * pDraw->sImage.height * (pDraw->sImage.pixelFormat == 5 ? 2 : 1);

	//ʹ��zlib��ѹ����
	BYTE* tWzlBuff = new BYTE[bmpRealSize];
	uLong outlen = bmpRealSize;

	//���λͼ����[���ɫ���Ӧ��λ������] //����ǣ���909 ���������ݽ��н�ѹ���õ���λͼ����
	uncompress(tWzlBuff, &outlen, tBuff, inlen);

	//���������ָ��ռ�
	pDraw->data = tWzlBuff;

	delete[] tBuff;

	fclose(fp);
}

////��������
//void GData::GWzlData::Load(HUM_STATE state, DIRECTION dir)
//{
//	FILE* fp;
//	//��ȡwzl
//	fopen_s(&fp, m_WzlFile, "r+b");
//	if (fp == NULL) {
//		return;
//	}
//
//	//����״̬ ����ͼƬ
//	int offset[8] = { 0 };
//	pWzx->GetOffset(state,dir, offset);
//
//	//��ȡ��Ӧ������ͼƬ�ز�
//	WzlImage image[8] = { 0 };
//	
//	for (int i = 0; i < ARRAYSIZE(offset); i++)
//	{
//		//wchar_t buf[50];
//		//swprintf_s(buf, TEXT("������%d \n"), offset[i]);
//		//OutputDebugString(buf);
//		if ( ! offset[i])
//		{
//			continue;
//		}
//
//		WzlImage& tImage = image[i];
//
//		//ָ��ͼƬ�ṹ��ͷ��λ��
//		fseek(fp, offset[i], SEEK_SET);
//
//		//��ȡ��ӦͼƬͷ���ṹ
//		fread(&tImage, sizeof(WzlImage), 1, fp);
//
//		//ƫ��+ͼƬ�ṹ��[ָ��ָ������]
//		fseek(fp, offset[i] + sizeof(WzlImage) - sizeof(void*), SEEK_SET);
//
//		//Դ����
//		BYTE* tBuff = nullptr;
//		tBuff = new BYTE[tImage.size];
//		uLongf inlen = tImage.size;
//
//		//��ȡͼƬ������
//		fread(tBuff, tImage.size, 1, fp);
//
//		//ͼƬʵ�ʴ�С (5 = 16λͼ D3DFMT_R5G6B5[2�����ݴ�С����])(3 = 32λͼ D3DFMT_A8R8G8B8)
//		int bmpRealSize = tImage.width * tImage.height * (tImage.pixelFormat == 5 ? 2 : 1);
//
//		//ʹ��zlib��ѹ����
//		BYTE* tWzlBuff = new BYTE[bmpRealSize];
//		uLong outlen = bmpRealSize;
//
//		//���λͼ����[���ɫ���Ӧ��λ������] //����ǣ���909 ���������ݽ��н�ѹ���õ���λͼ����
//		uncompress(tWzlBuff, &outlen, tBuff, inlen);
//
//		//���������ָ��ռ�
//		tImage.data = tWzlBuff;
//		delete[] tBuff;
//	}
//
//	fclose(fp);
//}
