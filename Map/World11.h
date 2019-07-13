#pragma once
#include "Scene.h"
#include "WorldMap.h"
#include "Framework/Animation.h"
#include <vector>

class World11 : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override;
	World11();
	~World11();
protected:
	WorldMap *map;
};