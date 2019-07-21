#pragma once
#include <d3dx9.h>
#include "WorldMap.h"

class Scene
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual WorldMap *GetCurrentMap() = 0;
	D3DCOLOR GetBackcolor();

	~Scene() {};
protected:
	Scene() {};
	D3DCOLOR BackColor;
};