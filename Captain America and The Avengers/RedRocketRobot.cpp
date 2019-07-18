#include "RedRocketRobot.h"



void RedRocketRobot::Update(float dt)
{
	this->current_animation->Update(dt);
	this->timer += dt;
	if (((int)round(this->timer) >> 1) % 2 == 0) {
		this->current_animation = this->idle_ani;
	}
	else {
		this->current_animation = this->ducking_ani;

	}
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
	this->idle_ani = new Animation(RedRocketRobotState::idle, L"Resources//Enemy//RedRocketRobot//RedRobotRocketIdle.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	this->running_ani = new Animation(RedRocketRobotState::running, L"Resources//Enemy//RedRocketRobot//RedRobotRocketRunning.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	this->ducking_ani = new Animation(RedRocketRobotState::ducking, L"Resources//Enemy//RedRocketRobot//RedRobotRocketDucking.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Enemy::beaten_ani = new Animation(RedRocketRobotState::beaten, L"Resources//Enemy//RedRocketRobot//RedRobotRocketBeaten.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	
	this->running_ani->SetTime(0.1);
	this->ducking_ani->SetTime(0.1);
	Enemy::beaten_ani->SetTime(0.1);
	

	this->red_rocket = new RedRocket();
	this->timer = 0.0f;




}


RedRocketRobot::~RedRocketRobot()
{
}
