#pragma once
#include "Enemy.h"
#include "RedRocket.h"
#include "Equation.h"
#include <vector>
#define GRAY_ROCKET_ROBOT_HP 5
#define TIME_DUCKING 2.0f
#define TIME_IDLE 2.0f
#define GRAY_ROCKET_ROBOT_SIZE_WIDTH 8
#define GRAY_ROCKET_ROBOT_SIZE_HEIGHT 44
#define GRAY_ROCKET_ROBOT_FOOT_HEIGHT 8
#define GRAY_ROCKET_ROBOT_VELOCITY 80
#define GRAY_ROCKET_ROBOT_VELOCITY_X 80
class GrayRocketRobot : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;

public:
	enum GrayRocketRobotState {
		running = 32,
		ducking = 33,
		beaten = 34,
		jumping
	};
	virtual void Update(float dt);
	virtual int OnCollision(Entity*, float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsRunning;
	bool IsDucking;
	bool IsIdle;
	bool IsExplode;
	bool IsHaveJump;
	bool IsLoop;
	bool IsCrossed;
	bool IsLock;
	bool IsLockChangeRocket;
	bool IsLockDuckingClever;
	bool IsChamDatLanDau;
	bool IsChamLanHai;
	bool IsFire;
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
	GrayRocketRobotState current_state;
	GrayRocketRobotState previous_state;
	int i = 0;
	Equation *e;
	GrayRocketRobot(D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, bool IsCrossed);
	~GrayRocketRobot() override;
};

