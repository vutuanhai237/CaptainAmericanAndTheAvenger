#pragma once
#include "Scene.h"
#include "PittsburghMap.h"

class Pittsburgh : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	WorldMap *GetCurrentMap() override;
	Grid *GetCurrentGrid() override;
	void SwapMap() override;
	void SwapMap(int code) override;
	int GetMode() override;
	bool UpdateOneTime;
	int number;
	float timer;
	float timer2;
	Pittsburgh();
	~Pittsburgh(); 
protected:
	PittsburghMap *map;
	Camera *cam;
private:
	void Init();
};

