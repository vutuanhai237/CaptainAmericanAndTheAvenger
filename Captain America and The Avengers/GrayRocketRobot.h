#pragma once
#include "Enemy.h"
#include "Equation.h"
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
	int i;
	int IsLui;
	int IsJumpingFirst;
	bool IsExplode;
	bool IsLoop;
	bool IsChamDatLanDau;
	bool IsFire;
	Entity::Entity_Direction goto_direction;
	GrayRocketRobotState current_state;
	GrayRocketRobotState previous_state;
	Equation *e;
	GrayRocketRobot(D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, bool IsCrossed);
	~GrayRocketRobot() override;
protected:
	Animation* running_ani;
	Animation* ducking_ani;
};

