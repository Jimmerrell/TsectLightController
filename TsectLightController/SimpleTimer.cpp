////////////////////////////////////////////////////////////////////////////////////
// File: SimpleTimer.cpp
// Authors: Jim Merrell
// Company:
// Purpose: 
////////////////////////////////////////////////////////////////////////////////////

#include "SimpleTimer.h"


SimpleTimer::SimpleTimer()
{
}

SimpleTimer::~SimpleTimer()
{
}

void SimpleTimer::Start()
{
	m_fStartTime = m_SysClock.now();
}

void SimpleTimer::Stop()
{
	m_fTotalClockTime += GetTimeInSeconds();
	m_fStopTime = m_SysClock.now().time_since_epoch();
}

float SimpleTimer::GetTimeInSeconds()
{
	auto CurrTime = m_SysClock.now();
	std::chrono::duration<float> RunTime = CurrTime - m_fStartTime;
	
	return RunTime.count();	// ((int)(RunTime.count()*1000.0f)) / 1000.0f;
}

std::string SimpleTimer::GetTimeInMinutesAndSeconds()
{
	std::string minutes = std::to_string((int)(GetTimeInSeconds() / 60));
	std::string seconds = std::to_string((int)GetTimeInSeconds() % 60);

	return minutes + " minutes and " + seconds + " seconds";
}

float SimpleTimer::GetTotalClockTime() const
{
	return m_fTotalClockTime;
}

