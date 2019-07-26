#pragma once
#include "Enemy.h"
#include "RedRocket.h"
#include "Equation.h"
#define BLUE_SOLDIER_TIME_DUCKING 2.0f
#define BLUE_SOLDIER_TIME_IDLE 2.0f
#define BLUE_SOLDIER_SIZE_WIDTH 8
#define BLUE_SOLDIER_SIZE_HEIGHT 44
#define BLUE_SOLDIER_FOOT_HEIGHT 8
#define BLUE_SOLDIER_VELOCITY 80
#define BLUE_SOLDIER_VELOCITY_X 80
class BlueSoldier : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
public:
	enum BlueSoldierState {
		none,
		idle,
		running,
		ducking,
		beaten,
		jumping,
		walking_throwing
	};
	enum Level {
		stupid,
		normal,
		clever
	};
	virtual void Update(float dt);
	virtual void UpdateStupidLevel(float dt);
	virtual void UpdateNormalLevel(float dt);
	virtual void UpdateCleverLevel(float dt);
	virtual int OnCollision(Entity*, float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;

	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsRunning;
	bool IsDucking;
	bool Isbeaten;
	bool IsIdle;
	bool IsHaveJump;
	bool IsLoop;
	bool IsCrossed;
	bool IsLock;
	bool IsLockChangeRocket;
	bool IsLockDuckingClever;
	bool IsChamDatLanDau;
	bool IsChamLanHai;

	bool IsLoopClever;
	bool IsCapNhatVanToc;
	bool IsCapNhatPositionMotLan;
	bool IsLockClever;

	int IsLui;
	int IsJumpingFirst;
	float time_ducking;
	float time_idle;
	int rocket_active;
	Entity::Entity_Direction goto_direction;
	Level level;
	BlueSoldierState current_state;
	BlueSoldierState previous_state;
	int i = 0;
	Equation *e;
	int NumberRocket;
	// clever zone
	float distance;
	float distance_goto;
	bool Update_position_one_time;
	Entity::Entity_Direction clever_direction;
	BlueSoldier(int level, D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, bool IsCrossed);
	
	~BlueSoldier() override;
};

