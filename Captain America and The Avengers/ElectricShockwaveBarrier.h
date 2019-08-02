#pragma once
#include "Entity.h"
class ElectricShockwaveBarrier : public Entity
{
public:
	ElectricShockwaveBarrier(int WorldX, int WorldY);
	~ElectricShockwaveBarrier();

	static int ID;
};

