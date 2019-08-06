#pragma once
#include "Entity.h"
#include "Player.h"
#include "Framework/Animation.h"
#include <math.h>
#include "SceneManager.h"
#define ENEMY_DAMAGE 1
#define ENEMY_TIME_BEATEN 0.5f
#define TIME_EXPLODE 0.25f
#define TIME_BEATEN 0.3f
class Enemy: public Entity
{
public:
	virtual Animation* GetCurrentAnimation();
	virtual void Update(float dt); 
	virtual int OnCollision(Entity*, float dt) override; 
	virtual void SetActive(bool IsActive) {}; 
	virtual void Delete() {}; 
	virtual void Spawn();
	virtual bool IsCollisionWithGround(float dt, int delta_y = 12);
	virtual void Draw();
	virtual void DrawInt();
	Enemy();
	virtual ~Enemy() override;
	int i = 0;
	int hp;
	float time_beaten;
	float time_explode;
	bool IsJumping;
	bool IsDead;
	bool IsBeaten;
	bool IsExplode;
protected:
	Animation* beaten_ani; 
	Animation* explode_ani;
	Animation* current_animation;
	D3DXVECTOR2 position_spawn;
	D3DXVECTOR2 position_goto;
	D3DXVECTOR2 position_loop;
};

