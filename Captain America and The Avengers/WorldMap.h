#pragma once
#include <vector>
#include "Framework/Sprite.h"
#include "Entity.h"
using namespace std;

#define MAPOBJ_GROUND 0
#define MAPOBJ_WALL 1
#define MAPOBJ_WATER 2
#define MAPOBJ_ROPE 3
#define MAPOBJ_ONOFF 4
#define MAPOBJ_WAVE 5
#define MAPOBJ_DOOR 6
#define MAPOBJ_SPIKE 7

class WorldMap : public Sprite
{
public:
	WorldMap(LPCWSTR FileTitleMap, int IDTitleMap);
	WorldMap(LPCWSTR FileTitleMap, LPCWSTR PathTitleMap);
	void Draw(D3DCOLOR ColorMode = Sprite::DefaultColorMode) override;
	
	void SetRect(int IDTitle);
	~WorldMap();
	SIZE GetMapSize();

	virtual vector<Entity*> *GetMapObj();
protected:
	void Init(LPCWSTR Path);
	int Width, Height;
	int **Map;

	vector<Entity*> MapObj;
};

