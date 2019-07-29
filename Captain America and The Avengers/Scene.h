#pragma once
#include <d3dx9.h>
#include "WorldMap.h"
#include "Grid.h"

class Scene
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual WorldMap *GetCurrentMap() = 0;
	virtual Grid *GetCurrentGrid() = 0;

	D3DCOLOR GetBackcolor();
	virtual void SwapMap() {};
	virtual void SwapMap(int code);
	virtual int GetMode();

	virtual ~Scene() {};

	bool IsExitAble;
protected:
	Scene();
	D3DCOLOR BackColor;
	RECT ExitZone;

	bool IsInsideExitZone();
	int Mode;
};