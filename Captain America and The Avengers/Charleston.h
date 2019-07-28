#pragma once
#include "Scene.h"
#include "CharlestonMap.h"
#include "Camera.h"
#include "Framework/Animation.h"
#include "Grid.h"
#include <vector>

class Charleston : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	Charleston();
	~Charleston() override;
protected:
	CharlestonMap *map;
	Camera *cam;
	Sprite* exit;
	Grid *grid;
private:
	void Init();
	void DrawExit();
	int FrameExitCounter;
	D3DXVECTOR2 FirstExitPosition;
};