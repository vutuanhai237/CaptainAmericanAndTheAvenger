#pragma once
#include "Scene.h"
#include "CharlestonBossMap.h"
#include "Camera.h"
#include "Framework/Animation.h"
#include <vector>
#include "Grid.h"
class CharlestonBoss : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	CharlestonBoss();
	~CharlestonBoss() override;
protected:
	void Init();
	CharlestonBossMap *map;
	Camera *cam;
	Grid *grid;
};