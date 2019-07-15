#pragma once
#include "Framework/Sprite.h"

class WorldMap : public Sprite
{
public:
	WorldMap(LPCWSTR FileTitleMap, int IDTitleMap);
	WorldMap(LPCWSTR FileTitleMap, LPCWSTR PathTitleMap);
	void Draw() override;
	void SetRect(int IDTitle);
	~WorldMap();
protected:
	void Init(LPCWSTR Path);

	int TotalTitle;
	int Width, Height;
	int **Map;
};

