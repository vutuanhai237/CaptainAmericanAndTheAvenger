#pragma once
#include "Entity.h"
#include "Player.h"
#include "Framework/Animation.h"
class EnemyWeapon : public Entity
{
public:
	virtual void Update(float dt) {};
	virtual void Render() {};
	virtual void OnCollision() {};
	virtual void SetActive(bool IsActive) {};
	EnemyWeapon();
	~EnemyWeapon();
protected:
	Animation* beaten;
	Animation* explode;

};

