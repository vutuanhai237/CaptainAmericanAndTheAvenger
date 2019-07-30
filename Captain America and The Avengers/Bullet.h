#pragma once
#include "EnemyWeapon.h"
#define BULLET_VELOCITY_X 200.0f
#define DISTANCE_OUT 400.0f
#define TIME_OUT_STRAIGHT 0.016*15
#define BULLET_DAMAGE 1
class Bullet : public EnemyWeapon
{
public:	
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	Bullet(D3DXVECTOR2, Entity::Entity_Direction direction, FLOAT direction_y = 0.0f);
	~Bullet() override;
	bool IsDead;
	float distance;
	Animation* current_ani;
protected:
	float time_out_straight;
};

