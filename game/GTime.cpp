#include "GTime.h"

ULONGLONG GTime::s_tNowTime = 0;
ULONGLONG GTime::s_tPrevTime = 0;
ULONGLONG GTime::s_tInitTime = GetTickCount64();

GTime::GTime()
{
	m_tPrevTime = s_tNowTime;
}

GTime::~GTime()
{
}

void GTime::run()
{
	s_tNowTime = (GetTickCount64() - s_tInitTime);
}

void GTime::over() {
	s_tPrevTime = s_tNowTime;
}

bool GTime::CountDown(int time)
{
	if (s_tNowTime - m_tPrevTime > time)
	{
		m_tPrevTime = s_tNowTime;
		return true;
	}
	return false;
}

float GTime::GetCountDown()
{
	return (s_tNowTime - s_tPrevTime) * 0.001f;
}


