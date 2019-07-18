#pragma once
#include "Scene.h"
#include "CharlestonMap.h"
#include "Camera.h"
#include "Framework/Animation.h"
#include <vector>

class Charleston : public Scene
{
public:
	void Update(float dt) override;
	void Draw() override; 
	WorldMap *GetCurrentMap() override;
	Charleston();
	~Charleston();
protected:
	void Init();
	CharlestonMap *map;
	Camera *cam;
	Animation* exit;
	int i;
};