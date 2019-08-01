#pragma once
#include "EnemyWeapon.h"

#define GRAY_ROCKET_DAME 2
#define GRAY_ROCKET_TIME_CHANGE_DIRECTION 0.125f
#define GRAY_ROCKET_TURN PI/4
#define GRAY_ROCKET_VELOCITY 200
#define GRAY_ROCKET_MIN_LOCATION_FOLLOW 40.0f

class GrayRocket : public EnemyWeapon
{
public:
	GrayRocket(FLOAT WorldX, FLOAT WorldY, Entity::Entity_Direction direction);
	~GrayRocket();
	void Update(float dt) override;
	int OnCollision(Entity*, float dt) override;
	void Exploding(float dt);
	void Draw() override;
	void Release();
	bool IsExploding;
	bool IsDead;

	float time_out_explode;
	static int ID;
private:
	Animation *current_ani;
	float radian;
	float Timer;
	int ChangeDirectionCounter;
};
