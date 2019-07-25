#pragma once
#include "EnemyWeapon.h"
#define RED_ROCKET_VELOCITY_X 120.0f
#define DISTANCE_OUT 235.0f
#define TIME_OUT_STRAIGHT 0.016*15
#define TIME_EXPLODE 0.016*10
class RedRocket : public EnemyWeapon
{

public:
	enum RedRocketState {
		crossed = 5,
		horizontal = 6,
		explode = 7
	};
	virtual void Update(float dt);
	virtual void OnCollision();
	virtual void Exploding(float dt, D3DXVECTOR2 position_respawn, int level_robot);
	virtual void Release();
	virtual void Draw();
	RedRocket();
	RedRocket(D3DXVECTOR2, bool IsCrossed);

	~RedRocket();
	bool IsFire;
	float distance;
	bool IsStraight;
	bool IsExploding;
	Animation* current_ani;

protected:
	
	bool IsCrossed;
	float time_out_explode;
	float time_out_straight;
	Animation* crossed_ani;
	Animation* horizontal_ani;
};

