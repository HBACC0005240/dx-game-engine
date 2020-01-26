#pragma once

//定义wzl对应wzx资源的偏移

//人物状态枚举
enum HUM_STATE
{
	STAND = 0,//4帧 空4帧
	WALK = 64,//6帧 空2帧
	RUN = 128,//6帧 空2帧
	BATTLE_POS = 192,//8帧 空0帧
	ATTACK = 200,//6帧 空2帧
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