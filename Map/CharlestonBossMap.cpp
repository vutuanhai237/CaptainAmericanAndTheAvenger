#include "CharlestonBossMap.h"
#include "Camera.h"

CharlestonBossMap::CharlestonBossMap()
{
	LightMap = new WorldMap(L"Resources/Map/charleston_boss_light_map.txt", 0);
	DarkMap = new WorldMap(L"Resources/Map/charleston_boss_dark_map.txt", 0);
	CurrentMapMode = MapMode::Light;
	Camera::GetInstance()->Init(LightMap->GetMapSize());
}

CharlestonBossMap::~CharlestonBossMap()
{
	delete LightMap;
	delete DarkMap;
}

void CharlestonBossMap::Draw()
{
	switch (CurrentMapMode)
	{
	case MapMode::Dark:
		DarkMap->Draw();
		break;
	case MapMode::Light:
		LightMap->Draw();
		break;
	}
}

void CharlestonBossMap::SwapMode()
{
	switch (CurrentMapMode)
	{
	case MapMode::Dark:
		CurrentMapMode = MapMode::Light;
		break;
	case MapMode::Light:
		CurrentMapMode = MapMode::Dark;
		break;
	}
}

void CharlestonBossMap::SwapMode(MapMode mode)
{
	CurrentMapMode = mode;
}

WorldMap *CharlestonBossMap::GetCurrentMap()
{
	switch (CurrentMapMode)
	{
	case MapMode::Dark:
		return DarkMap;
	case MapMode::Light:
		return LightMap;
	}
}
