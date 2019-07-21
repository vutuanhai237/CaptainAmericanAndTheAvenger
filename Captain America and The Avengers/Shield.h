#pragma once
#include "Entity.h"
#include "ShieldState.h"
#include "Framework/Animation.h"


class Shield : private Entity
{
public:
	static Shield *GetInstance();
	void Release();

	void Update(float dt);
	void Draw();

	void SetShieldState(ShieldState *state);
	Animation *GetAnimation();
protected:
	Animation *shield;
	ShieldState *state;
private:
	Shield();
	~Shield();
	static Shield *Instance;
};