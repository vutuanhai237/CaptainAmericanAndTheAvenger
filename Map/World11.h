#pragma once
#include "Scene.h"
#include "WorldMap.h"
#include "Framework/Animation.h"
#include "PlayerState.h"
#include "Player.h"
#include <vector>

class World11 : public Scene
{
public:
	std::vector<Animation*> sprites;
	void Update(float dt) override;
	void Draw() override;
	void Init();
	World11();
	~World11();
protected:
	//WorldMap *map;

	
};