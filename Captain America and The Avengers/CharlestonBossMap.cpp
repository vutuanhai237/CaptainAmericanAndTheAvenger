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
	if (CurrentMapMode == MapMode::Dark)
		DarkMap->Draw();
	else
		LightMap->Draw();
}

void CharlestonBossMap::SwapMode()
{
	if (CurrentMapMode == MapMode::Light)
		CurrentMapMode = MapMode::Dark;
	else
		CurrentMapMode = MapMode::Light;
}

void CharlestonBossMap::SwapMode(MapMode mode)
{
	CurrentMapMode = mode;
}

WorldMap *CharlestonBossMap::GetCurrentMap()
{
	if (CurrentMapMode == MapMode::Dark)
		return DarkMap;
	else
		return LightMap;
}

SIZE CharlestonBossMap::GetMapSize()
{
	return GetCurrentMap()->GetMapSize();
}
