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
	Charleston();
	~Charleston();
	void Init();
protected:
	CharlestonMap *map;
	Camera *cam;
};