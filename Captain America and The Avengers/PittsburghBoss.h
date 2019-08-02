#pragma once
#include "Scene.h"
#include "PittsburghBossMap.h"
#include "Camera.h"
#include <vector>
class PittsburghBoss : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	PittsburghBoss();
	~PittsburghBoss() override;
protected:
	PittsburghBossMap *map;
	Camera *cam;
	Grid *grid;
private:
	void Init();
};