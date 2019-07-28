#pragma once
#include "WorldMap.h"

class CharlestonBossMap
{
public:
	CharlestonBossMap();
	~CharlestonBossMap();

	enum MapMode {Dark, Light};

	void Draw();
	void SwapMode();
	void SwapMode(MapMode mode);

	WorldMap *GetCurrentMap();
	SIZE GetMapSize();
private:
	WorldMap *LightMap, *DarkMap;
	MapMode CurrentMapMode;
};