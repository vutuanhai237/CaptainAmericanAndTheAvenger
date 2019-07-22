#pragma once
#include "EnemyWeapon.h"
#define RED_ROCKET_VELOCITY_X 80.0f
#define DISTANCE_OUT 1000.0f
class RedRocket : public EnemyWeapon
{

public:
	enum RedRocketState {
		crossed = 5,
		horizontal = 6
	};
	virtual void Update(float dt);
	virtual void Render();
	virtual void OnCollision();
	virtual void Release();
	virtual void Draw();
	RedRocket();
	RedRocket(D3DXVECTOR2);

	~RedRocket();
	bool IsFire;
	float distance;
	Animation* current_ani;

protected:
	bool IsCrossed;

	Animation* crossed_ani;
	Animation* horizontal_ani;
};

