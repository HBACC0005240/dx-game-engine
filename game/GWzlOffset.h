#pragma once

//����wzl��Ӧwzx��Դ��ƫ��

//����״̬ö��
enum HUM_STATE
{
	STAND = 0,//4֡ ��4֡
	WALK = 64,//6֡ ��2֡
	RUN = 128,//6֡ ��2֡
	BATTLE_POS = 192,//8֡ ��0֡
	ATTACK = 200,//6֡ ��2֡
};

//���﷽��ö�� 0~7
enum DIRECTION
{
	UP = 0,
	RIGHT_UP = 1,
	RIGHT = 2,
	RIGHT_DOWN = 3,
	DOWN = 4,
	LEFT_DOWN = 5,
	LEFT = 6,
	LEFT_UP = 7,
};

//WzlͼƬ��Ϣ�ṹ
struct WzlImage {
	byte pixelFormat;  // ͼƬλ��
	byte compressed;   // ��ʾͼƬ�����Ƿ񾭹�gzipѹ��
	byte reserve;
	byte compressLevel; // ���ͼƬ������ѹ����������ͱ�ʾѹ���ĵȼ�
	short width;  // ͼƬ���
	short height;  // ͼƬ�߶�
	short x;	//ƫ��x
	short y;	//ƫ��y
	int size;  // ͼƬ���ݳ���[ѹ�����]
};