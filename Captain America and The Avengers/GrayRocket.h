#pragma once
#include "EnemyWeapon.h"

#define GRAY_ROCKET_DAME 2
#define GRAY_ROCKET_TIME_CHANGE_DIRECTION 0.125f
#define GRAY_ROCKET_TURN PI/4
#define GRAY_ROCKET_VELOCITY 200
#define GRAY_ROCKET_MIN_LOCATION_FOLLOW 50.0f

class GrayRocket : public EnemyWeapon
{
public:
	GrayRocket(FLOAT WorldX, FLOAT WorldY, Entity::Entity_Direction direction);
	~GrayRocket();
	void Update(float dt) override;
	void Draw() override;

	static int ID;
private:
	Animation *rocket;
	float radian;
	float Timer;
	int ChangeDirectionCounter;
};
