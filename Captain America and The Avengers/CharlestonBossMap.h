#pragma once
#include "WorldMap.h"

class CharlestonBossMap
{
public:
	enum MapMode { 
		Dark, 
		Light 
	};
	CharlestonBossMap();
	~CharlestonBossMap();
	void Draw();
	void SwapMode();
	void SwapMode(MapMode mode);
	MapMode GetMode();
	WorldMap *GetCurrentMap();
	SIZE GetMapSize();
private:
	WorldMap *LightMap, *DarkMap;
	MapMode CurrentMapMode;
};