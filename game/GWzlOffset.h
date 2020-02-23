#pragma once

//����wzl��Ӧwzx��Դ��ƫ��

//����״̬ö��
enum HUM_STATE
{
	STAND		= 0,//4֡ ��4֡
	WALK		= STAND + 64,//6֡ ��2֡
	RUN			= WALK + 64,//6֡ ��2֡
	ATTACK_POS	= RUN + 64,//8֡ ��0֡
	ATTACK		= ATTACK_POS + 8,//6֡ ��2֡[���ֹ���]
	ATTACK2		= ATTACK + 64,//6֡ ��2֡[�ڿ�]
	ATTACK3		= ATTACK2 + 64,//8֡ ��0֡[����]
	SPELLS		= ATTACK3 + 64,//6֡ ��2֡[ʩ��]
	DIG_MEAT	= SPELLS + 64,//2֡ ��0֡[����]
	INJURED		= DIG_MEAT + 16,//3֡ ��5֡[����]
	DEATH		= INJURED + 64,//4֡ ��4֡[����]
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

struct DIR_ANGLE
{
	float begin = 0.0f;
	float end = 0.0f;
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