#pragma once
#include "EnemyWeapon.h"
#include "Equation.h"
#define LASER_BULLET_VELOCITY_X 150.0f
class LaserBullet : public EnemyWeapon
{

public:
	enum LaserBulletType {
		horizontal,
		vertical,
		crossed
	};
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	LaserBullet(D3DXVECTOR2, Entity::Entity_Direction direction);
	~LaserBullet() override;
	bool IsDead;
	bool IsComeBack;
	float distance;
	Equation* e;
	Animation* current_ani;
protected:
	float time_out_straight;
};

