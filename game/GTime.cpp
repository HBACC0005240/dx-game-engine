#include "GTime.h"

ULONGLONG GTime::s_tNowTime = 0;
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

bool GTime::CountDown(int time)
{
	if (s_tNowTime - m_tPrevTime > time)
	{
		m_tPrevTime = s_tNowTime;
		return true;
	}
	return false;
}


