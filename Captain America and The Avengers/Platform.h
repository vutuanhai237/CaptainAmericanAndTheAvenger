#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
	Platform(FLOAT WorldX, FLOAT WorldY);
	virtual ~Platform();
	static int DisappearPlatformID;
	static int MovingPlatformID;
	static int JetEngineVerticalID;
	static int JetEngineHorizontalID;
};

