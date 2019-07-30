#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Equation.h"
#define GREEN_SOLDIER_HP 2
#define GREEN_SOLDIER_TIME_IDLE_TO_SHOT 0.3f
#define GREEN_SOLDIER_TIME_RUNNING_TO_SHOT 0.7f
#define GREEN_SOLDIER_TIME_DUCKING 0.5f
#define GREEN_SOLDIER_TIME_IDLE 0.5f
#define GREEN_SOLDIER_SIZE_WIDTH 8
#define GREEN_SOLDIER_SIZE_HEIGHT 44
#define GREEN_SOLDIER_FOOT_HEIGHT 8
#define GREEN_SOLDIER_VELOCITY_Y 80
#define GREEN_SOLDIER_VELOCITY_X 80
class Bat : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
public:
	// Share zone
	enum BatState {
		none,
		idle = 17,
		running = 18,
		ducking = 19,
		beaten = 20,
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
	BatState current_state;
	BatState previous_state;
	Bat(int level, D3DXVECTOR2 position_spawn, int direction);
	~Bat() override;
};

