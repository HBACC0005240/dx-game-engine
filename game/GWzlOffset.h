#pragma once

//定义wzl对应wzx资源的偏移

//人物状态枚举
enum HUM_STATE
{
	STAND		= 0,//4帧 空4帧
	WALK		= STAND + 64,//6帧 空2帧
	RUN			= WALK + 64,//6帧 空2帧
	ATTACK_POS	= RUN + 64,//8帧 空0帧
	ATTACK		= ATTACK_POS + 8,//6帧 空2帧[单手攻击]
	ATTACK2		= ATTACK + 64,//6帧 空2帧[挖矿]
	ATTACK3		= ATTACK2 + 64,//8帧 空0帧[跳砍]
	SPELLS		= ATTACK3 + 64,//6帧 空2帧[施法]
	DIG_MEAT	= SPELLS + 64,//2帧 空0帧[挖肉]
	INJURED		= DIG_MEAT + 16,//3帧 空5帧[受伤]
	DEATH		= INJURED + 64,//4帧 空4帧[受伤]
};

//人物方向枚举 0~7
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

//Wzl图片信息结构
struct WzlImage {
	byte pixelFormat;  // 图片位深
	byte compressed;   // 表示图片数据是否经过gzip压缩
	byte reserve;
	byte compressLevel; // 如果图片数据是压缩过，这个就表示压缩的等级
	short width;  // 图片宽度
	short height;  // 图片高度
	short x;	//偏移x
	short y;	//偏移y
	int size;  // 图片数据长度[压缩后的]
};