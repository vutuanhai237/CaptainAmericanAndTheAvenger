#pragma once
#include "Scene.h"
#include "CharlestonBossMap.h"
#include "Camera.h"
#include <vector>

class CharlestonBoss : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	void SwapMap() override;
	void SwapMap(int code) override;
	int GetMode() override;
	CharlestonBoss();
	~CharlestonBoss() override;
protected:
	float time_count;
	int count_bullet;
	bool UpdateOneTime;
	CharlestonBossMap *map;
	Camera *cam;
	Grid *grid;
private:
	void Init();
};