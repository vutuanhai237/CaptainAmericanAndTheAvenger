#include "RedRocketRobot.h"



void RedRocketRobot::Update(float dt)
{
	Player *player = Player::GetInstance();
	if (player->GetPosition().x - this->GetPosition().x > 0) {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);

	}
	this->current_animation->Update(dt);
	while (this->position_spawn.x - this->position_goto.x > 3) {
		return;
	}

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
	if (this->IsCollisionWithGround(dt, 6))
	{
		return;
	}
	else {
		this->SetPositionY(this->GetPosition().y - 5);
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

void RedRocketRobot::Draw()
{
	this->current_animation->Draw(this->position);
}

bool RedRocketRobot::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = RED_ROCKET_ROBOT_SIZE_WIDTH;
	FootSize.cy = RED_ROCKET_ROBOT_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::ground && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::ground)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + RED_ROCKET_ROBOT_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
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
	this->SetVelocityY(-5.0f);
	//
	if (position_spawn.x > position_goto.x) {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);

	}
	this->SetVelocityX(RED_ROCKET_ROBOT_VELOCITY);
}


RedRocketRobot::~RedRocketRobot()
{
}
