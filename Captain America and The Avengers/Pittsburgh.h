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

	Pittsburgh();
	~Pittsburgh(); 
protected:
	PittsburghMap *map;
	Camera *cam;
private:
	void Init();
};

