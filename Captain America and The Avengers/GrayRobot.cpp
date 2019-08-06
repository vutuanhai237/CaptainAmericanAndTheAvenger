#include "GrayRobot.h"
#include "Shield.h"
#include "FrameWork/SoundManager.h"
#include "GrayRocket.h"
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
			SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
		}
		return;
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
	if (this->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
		this->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		this->GetCurrentAnimation()->SetScale(-1, 1);
	}
	if (this->IsBeaten) {
		this->current_animation->Draw(this->position);
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
	t -= dt;
	this->position.x = this->virtual_point.x + (Ax * cos(omega*t + PI));
	this->position.y = this->virtual_point.y + (Ay * cos(omega*t - PI/2));
	this->time_fire += dt;
	if (this->time_fire > 2) {
		this->current_state = GrayRobotState::firing;
		this->time_fire = 0;
	}
	if (Player::GetInstance()->GetPosition().x <= this->GetPosition().x) {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		this->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		this->GetCurrentAnimation()->SetScale(-1, 1);
	}
}

void GrayRobot::UpdateFiringState(float dt)
{
	if (this->UpdateOneTime2 == false)
	{
		this->SetVelocity(0, 0);
		this->current_animation = firing_ani;
		this->UpdateOneTime2 = true;
		
		
	}
	this->time_fire += dt;
	if (this->time_fire > 0.3f && this->count_bullet == 0) {
		if (this->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new GrayRocket(
					this->position.x - 11.5, this->position.y + 13.5,
					this->GetMoveDirection()
				)
			);
		}
		else {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new GrayRocket(
					this->position.x + 11.5, this->position.y + 13.5,
					this->GetMoveDirection()
				)
			);
		}
		this->count_bullet++;
	}
	if (this->time_fire > GRAY_ROBOT_TIME_FIRING) {
		this->time_fire = 0;
		this->UpdateOneTime2 = false;
		this->current_animation = idle_ani;
		this->current_state = GrayRobotState::idle;
		this->count_bullet = 0;
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
	this->Ax = distance;
	this->Ay = distance * 0.35;
	this->omega = 2 * PI / 4;
	this->t = 0;
	this->virtual_point = this->position;
	this->position_spawn = position_spawn;
	this->current_animation = idle_ani;
	this->current_state = GrayRobotState::idle;
	this->hp = GRAY_ROBOT_HP;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->time_fire = 0.0f;
	this->distance = distance;
	this->IsLui = 0;
	this->count_bullet = 0;
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

