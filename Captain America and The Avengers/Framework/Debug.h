#pragma once
#include <Windows.h>
#include <stdio.h>

class Debug
{
public:
	static void PrintOut(const wchar_t *fmt, ...);
private:
	Debug() {};
	~Debug() {};
};

