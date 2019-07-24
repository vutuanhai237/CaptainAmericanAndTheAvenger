#pragma once
#include "EnemyWeapon.h"
#define RED_ROCKET_VELOCITY_X 120.0f
#define DISTANCE_OUT 240.0f
#define TIME_OUT_STRAIGHT 0.016*15
class RedRocket : public EnemyWeapon
{

public:
	enum RedRocketState {
		crossed = 5,
		horizontal = 6
	};
	virtual void Update(float dt);
	virtual void OnCollision();
	virtual void Release(D3DXVECTOR2 position_respawn);
	virtual void Draw();
	RedRocket();
	RedRocket(D3DXVECTOR2, bool IsCrossed);

	~RedRocket();
	bool IsFire;
	float distance;
	bool IsStraight;

	Animation* current_ani;

protected:
	bool IsCrossed;
	float time_out_straight;
	Animation* crossed_ani;
	Animation* horizontal_ani;
};

