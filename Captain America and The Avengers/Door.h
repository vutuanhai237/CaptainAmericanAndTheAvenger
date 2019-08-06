#pragma once
#include "Entity.h"
#include "Framework/Animation.h"

class Door : public Entity
{
public:
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	void Draw() override;
	static int IDDarkDoor;
	static int IDLightDoor;
	Door(int WorldX, int WorldY, int GotoCode, int PositionGotoX, int PositionGotoY);
	~Door();
private:
	std::vector<Animation*> *animation;
	int GotoCode;
	D3DXVECTOR2 PositionGoto;
};

