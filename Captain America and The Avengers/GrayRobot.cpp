#include "GrayRobot.h"
#include "Shield.h"
#include "FrameWork//Debug.h"
#include "RedRocket.h"
void GrayRobot::Update(float dt)
{
	Enemy::Update(dt);
	this->current_animation->Update(dt);
	if (this->IsExplode) {
		this->time_explode += dt;
		this->current_state = GrayRobotState::none;
		this->current_animation = explode_ani;
		this->SetVelocity(0, 0);

		if (this->time_explode >= TIME_EXPLODE) {
			this->IsDead = true;
			this->IsActive = false;
		}
		return;
	}
	if (this->IsBeaten) {
		this->current_state = GrayRobotState::beaten;
		this->current_animation = beaten_ani;
		this->SetVelocity(0, -GRAY_ROBOT_VELOCITY_Y);
		this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		if (this->IsCollisionWithGround(dt)) {
			this->IsExplode = true;
		}
		return;
	}

	
	if (this->UpdateOneTime == false) {
		this->e = new Eclipse(this->position_spawn, this->GetMoveDirection(), this->distance);
		this->UpdateOneTime = true;
	}

	if (this->current_state == GrayRobotState::idle) {
		this->UpdateIdleState(dt);
	}
	if (this->current_state == GrayRobotState::firing) {
		this->UpdateFiringState(dt);
	}
}

int GrayRobot::OnCollision(Entity* obj, float dt)
{
	return Enemy::OnCollision(obj, dt);
}

void GrayRobot::Draw()
{
	if (this->IsBeaten) {
		this->current_animation->Draw(this->position);
		goto CHECK;
	}
	if (this->time_beaten == 0) {
		this->current_animation->Draw(this->position);

	}
	else {
		this->time_beaten -= 0.016;
		if (this->time_beaten <= 0) {
			this->time_beaten = 0;
		}
		if ((i++) % 3 == 1) {
			this->current_animation->Draw(this->position);

		}

	}
CHECK:
	if (Player::GetInstance()->GetPosition().x <= this->GetPosition().x) {
		this->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		this->GetCurrentAnimation()->SetScale(-1, 1);
	}
}

BoundingBox GrayRobot::GetBoundingBox()
{
	SIZE size;
	size.cx = 24;
	size.cy = 46;
	return BoundingBox(Entity::position, size, Entity::velocity.x, Entity::velocity.y);
}

void GrayRobot::UpdateIdleState(float dt)
{
	auto keyboard = DirectInput::GetInstance();
	if (keyboard->KeyPress(DIK_D)) IsLui = -1;
	if (keyboard->KeyPress(DIK_F)) IsLui = 1;

	//if (abs(this->position.x == this->position_loop.x)) IsLui = 1;	
	//if (abs(this->position.x == this->position_goto.x) < 2.0f) IsLui = -1;
	if (IsLui == 1) {
		if (this->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
			this->position.x += GRAY_ROBOT_VELOCITY_X * dt;
			if (this->position.x > this->position_loop.x) {
				this->position.x = this->position_loop.x;
				this->current_state = GrayRobotState::firing;

				this->IsLui = -1;
			}
			if (this->e != NULL) {
				this->SetPositionY(e->GetYFromX(abs(this->GetPosition().x-this->position_spawn.x), this->IsLui) + this->position_spawn.y);
			}
		}
		else {
			this->position.x -= GRAY_ROBOT_VELOCITY_X * dt;
			if (this->position.x > this->position_loop.x) {
				this->position.x = this->position_loop.x;
				this->current_state = GrayRobotState::firing;

				this->IsLui = -1;
			}
			if (this->e != NULL) {
				this->SetPositionY(e->GetYFromX(abs(this->GetPosition().x - this->position_spawn.x), this->IsLui) + this->position_spawn.y);
			}
		}
	}
	if (IsLui == -1) {
		if (this->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
			this->position.x -= GRAY_ROBOT_VELOCITY_X * dt;
			if (this->position.x < this->position_goto.x) {
				this->position.x = this->position_goto.x;
				this->current_state = GrayRobotState::firing;

				this->IsLui = 1;
			}
			if (this->e != NULL) {
				this->SetPositionY(e->GetYFromX(abs(this->GetPosition().x - this->position_spawn.x), this->IsLui) + this->position_spawn.y);
			}
		}
		else {
			this->position.x += GRAY_ROBOT_VELOCITY_X * dt;
			if (this->position.x < this->position_goto.x) {
				this->position.x = this->position_goto.x;
				this->current_state = GrayRobotState::firing;

				this->IsLui = 1;
			}
			if (this->e != NULL) {
				this->SetPositionY(e->GetYFromX(abs(this->GetPosition().x - this->position_spawn.x), this->IsLui) + this->position_spawn.y);
			}
		}
	}

}

void GrayRobot::UpdateFiringState(float dt)
{
	if (this->UpdateOneTime2 == false)
	{
		this->SetVelocity(0, 0);
		this->current_animation = firing_ani;
		this->UpdateOneTime2 = true;
		if (Player::GetInstance()->GetPosition().x <= this->GetPosition().x) {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new RedRocket(
					D3DXVECTOR2(this->position.x - 11.5, this->position.y + 13.5),
					0,
					this->GetMoveDirection()
				)
			);
		}
		else {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new RedRocket(
					D3DXVECTOR2(this->position.x + 11.5, this->position.y + 13.5),
					0,
					this->GetMoveDirection()
				)
			);
		}
		
	}
	this->time_fire += dt;
	if (this->time_fire > GRAY_ROBOT_TIME_FIRING) {
		this->time_fire = 0;
		this->UpdateOneTime2 = false;
		this->current_animation = idle_ani;
		this->current_state = GrayRobotState::idle;
	}
}


GrayRobot::GrayRobot(D3DXVECTOR2 position_spawn, float distance) : Enemy()
{
	// init animation zone
	this->SetTag(Entity::Entity_Tag::gray_robot);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->idle_ani = new Animation(GrayRobotState::idle, 2);
	this->firing_ani = new Animation(GrayRobotState::firing, 2);
	this->beaten_ani = new Animation(GrayRobotState::beaten, 2);
	// set animation zone
	this->idle_ani->SetTime(0.1);
	this->firing_ani->SetTime(0.5);
	this->beaten_ani->SetTime(0.1);
	// set properties zone
	this->position = position_spawn;
	this->position_spawn = position_spawn;
	this->current_animation = idle_ani;
	this->current_state = GrayRobotState::idle;
	this->hp = GRAY_ROBOT_HP;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->time_fire = 0.0f;
	this->distance = distance;
	this->IsLui = 0;
	// init properties
	if (Player::GetInstance()->GetPosition().x > this->position.x) {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		this->position_goto = D3DXVECTOR2(this->position.x + distance, this->position.y);
		this->position_loop = D3DXVECTOR2(this->position.x - distance, this->position.y);

	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		this->position_goto = D3DXVECTOR2(this->position.x - distance, this->position.y);
		this->position_loop = D3DXVECTOR2(this->position.x + distance, this->position.y);

	}
	
}

bool GrayRobot::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = GRAY_ROBOT_SIZE_WIDTH;
	FootSize.cy = GRAY_ROBOT_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
		tmp = Checker->SweptAABB(foot, box2);
		if (tmp.side == CollisionSide::bottom)
		{
			return true;
		}		
	}
	return false;
}

GrayRobot::~GrayRobot()
{
}

