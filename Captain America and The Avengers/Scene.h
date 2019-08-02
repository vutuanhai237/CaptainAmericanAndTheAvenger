#pragma once
#include <d3dx9.h>
#include "WorldMap.h"
#include "Grid.h"

class Scene
{
public:
	virtual void Update(float dt);
	virtual void Draw();
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
	int Mode;

	bool IsInsideExitZone();
private:
	Sprite* exit;
	int FrameExitCounter;
	D3DXVECTOR2 FirstExitPosition;
	void DrawExit();
};