#pragma once
#include "Core.h"
class GTime {

public:
	static ULONGLONG s_tNowTime;
	static ULONGLONG s_tInitTime;
	ULONGLONG m_tPrevTime;
public:
	GTime();
	~GTime();

	static void run();

	bool CountDown(int time);
};