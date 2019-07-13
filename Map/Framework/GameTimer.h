#pragma once
#include <Windows.h>

class GameTimer
{
public:
	void StartCounter();
	float GetCounter();
	static GameTimer* GetInstance();
	void Release();
private:
	GameTimer() {};
	~GameTimer() {};

	LARGE_INTEGER StartTime, EndTime, Delta, ClockRate;
	static GameTimer *Instance;
};