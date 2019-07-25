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
	void Init();
	CharlestonMap *map;
	Camera *cam;
	Animation* exit;
	Grid *grid;
	int i;
};