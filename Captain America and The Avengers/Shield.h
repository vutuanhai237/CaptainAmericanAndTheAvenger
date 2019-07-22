#pragma once
#include "Entity.h"
#include "ShieldState.h"
#include "Framework/Animation.h"


class Shield : public Entity
{
public:
	static Shield *GetInstance();
	void Release();

	void Update(float dt);
	void Draw();

	void SetShieldState(ShieldState *state);
	ShieldState *GetShieldState();
	ShieldState *GetBufferState();
	Animation *GetAnimation();

protected:
	Animation *shield;
	ShieldState *state, *buffer;

private:
	Shield();
	~Shield();
	static Shield *Instance;
};