#pragma once
#include "EnemyWeapon.h"
#define SUPER_LASER_BULLET_VELOCITY_X 250.0f
#define SUPER_LASER_BULLET_DAMAGE 3
class SuperLaserBullet : public EnemyWeapon
{

public:
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Exploding(float dt);
	virtual void Release();
	virtual void Draw();
	SuperLaserBullet(D3DXVECTOR2, Entity::Entity_Direction direction);

	~SuperLaserBullet() override;
	bool IsDead;
	float distance;
	bool IsStraight;
	bool IsExploding;
	Animation* current_ani;

protected:
	float time_out_explode;
	float time_out_straight;
};

