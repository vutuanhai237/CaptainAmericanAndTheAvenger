#include "RedRocketRobot.h"



void RedRocketRobot::Update(float dt)
{
	if (this->IsCollisionWithGround(dt, 8))
	{
		return;
	}
	this->current_animation->Update(dt);
	if (this->IsIdle) {
		this->time_idle += dt;
	}
	if (this->IsDucking) {
		this->time_ducking += dt;
	}
	if (this->time_idle >= 2.0f) {
		this->IsIdle = false;
		this->IsDucking = true;
		this->current_animation = this->ducking_ani;
		this->time_idle = 0.0f;
	}
	if (this->time_ducking >= 2.0f) {
		this->IsDucking = false;
		this->IsIdle = true;
		this->current_animation = this->idle_ani;
		this->time_ducking = 0.0f;
	}
	this->current_animation->Update(dt);

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

void RedRocketRobot::Draw()
{
	this->current_animation->Draw(this->position);
}

RedRocketRobot::RedRocketRobot()
{
	this->idle_ani = new Animation(RedRocketRobot::RedRocketRobotState::idle, 2);
	this->running_ani = new Animation(RedRocketRobot::RedRocketRobotState::running, 3);
	this->ducking_ani = new Animation(RedRocketRobot::RedRocketRobotState::ducking, 2);
	this->beaten_ani = new Animation(RedRocketRobot::RedRocketRobotState::beaten, 1);
	//
	this->idle_ani->SetTime(0.5);
	this->running_ani->SetTime(0.1);
	this->ducking_ani->SetTime(0.5);
	//
	this->red_rocket = new RedRocket();
	this->time_ducking = 0.0f;
	this->IsDucking = false;
	this->IsIdle = true;
	this->current_state = RedRocketRobotState::idle;
	this->current_animation = idle_ani;
}


RedRocketRobot::~RedRocketRobot()
{
}
