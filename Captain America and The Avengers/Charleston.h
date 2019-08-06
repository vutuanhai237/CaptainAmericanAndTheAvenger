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
	float timer;
	float timer2;
	bool UpdateOneTime;
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	Charleston();
	~Charleston() override;
protected:
	CharlestonMap *map;
	Camera *cam;
	Grid *grid;
private:
	void Init();
};