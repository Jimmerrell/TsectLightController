////////////////////////////////////////////////////////////////////////////////////
// File: SimpleTimer.h
// Authors: Jim Merrell
// Company:
// Purpose: 
////////////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(disable : 4820)
#include <string>
#include <chrono>
#include <ctime>

class SimpleTimer
{
public:
	SimpleTimer();
	~SimpleTimer();

	void Start();
	void Stop();

	float GetTimeInSeconds();
	std::string GetTimeInMinutesAndSeconds();

	float GetTotalClockTime() const; 
private:
	std::chrono::time_point<std::chrono::system_clock> m_fStartTime;
	std::chrono::duration<float> m_fStopTime;

	std::chrono::system_clock m_SysClock;
	
	float m_fTotalClockTime = 0.0f;
};

