#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Equation.h"
#define BLUE_SOLDIER_TIME_IDLE_TO_SHOT 0.3f
#define BLUE_SOLDIER_TIME_RUNNING_TO_SHOT 1.0f
#define BLUE_SOLDIER_TIME_DUCKING 2.0f
#define BLUE_SOLDIER_TIME_IDLE 2.0f
#define BLUE_SOLDIER_SIZE_WIDTH 8
#define BLUE_SOLDIER_SIZE_HEIGHT 44
#define BLUE_SOLDIER_FOOT_HEIGHT 8
#define BLUE_SOLDIER_VELOCITY_Y 80
#define BLUE_SOLDIER_VELOCITY_X 80
class BlueSoldier : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
public:
	// Share zone
	enum BlueSoldierState {
		idle = 8,
		running = 9,
		ducking = 10,
		beaten = 11,
		jumping,
		walking_throwing
	};
	enum Level {
		stupid,
		normal,
		clever
	};
	Level level;
	int i = 0;
	Equation *e;
	float distance;
	bool IsChamDatLanDau;
	bool IsFire;
	// stupid zone
	float time_idle;
	float time_ducking;
	bool IsDucking;
	bool IsIdle;
	// clever level
	int IsJumpingFirst;
	float time_running;
	bool IsRunning;
	// Function
	virtual void Update(float dt);
	virtual void UpdateStupidLevel(float dt);
	virtual void UpdateNormalLevel(float dt);
	virtual void UpdateCleverLevel(float dt);
	virtual int OnCollision(Entity*, float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	BlueSoldierState current_state;
	BlueSoldierState previous_state;
	BlueSoldier(int level, D3DXVECTOR2 position_spawn, int direction);
	~BlueSoldier() override;
};

