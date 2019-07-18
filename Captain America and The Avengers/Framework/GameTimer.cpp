#include "GameTimer.h"
#include <time.h>

GameTimer* GameTimer::Instance = NULL;

void GameTimer::StartCounter()
{
	if (!QueryPerformanceFrequency(&ClockRate))
		return;
	QueryPerformanceCounter(&StartTime);
}

float GameTimer::GetCounter()
{
	QueryPerformanceCounter(&EndTime);
	Delta.QuadPart = EndTime.QuadPart - StartTime.QuadPart;
	return ((float)Delta.QuadPart / ClockRate.QuadPart);
}

GameTimer* GameTimer::GetInstance()
{
	if (!Instance)
		Instance = new GameTimer();
	return Instance;
}

void GameTimer::Release()
{
	delete Instance;
}
