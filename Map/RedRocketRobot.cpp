#include "RedRocketRobot.h"



void RedRocketRobot::Update(float dt)
{
}

void RedRocketRobot::Render()
{
}

void RedRocketRobot::OnCollision()
{
}

void RedRocketRobot::SetActive(bool IsActive)
{
}

RedRocketRobot::RedRocketRobot()
{
	this->running_ani = new Animation(RedRocketRobotState::running, L"Resources//Enemy//RedRocketRobot//RedRobotRocketRunning.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	this->ducking_ani = new Animation(RedRocketRobotState::ducking, L"Resources//Enemy//RedRocketRobot//RedRobotRocketDucking.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Enemy::beaten_ani = new Animation(RedRocketRobotState::beaten, L"Resources//Enemy//RedRocketRobot//RedRobotRocketBeaten.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	this->red_rocket = new RedRocket();
}


RedRocketRobot::~RedRocketRobot()
{
}
