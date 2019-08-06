#include "ElectricShockwaveBarrier.h"
#include "Player.h"
#include "PlayerShockingState.h"

int ElectricShockwaveBarrier::ID = -1;

ElectricShockwaveBarrier::ElectricShockwaveBarrier(int WorldX, int WorldY) : Entity()
{
	Entity::tag = Entity::Entity_Tag::electric_shockwave_barrier;
	Entity::type = Entity::Entity_Type::static_type;
	Entity::position.x = (FLOAT)WorldX;
	Entity::position.y = (FLOAT)WorldY;
	Entity::size.cx = 16;
	Entity::size.cy = 48;
	animation = new Animation(ElectricShockwaveBarrier::ID, 6);
	animation->SetTime(2 / 60.0f);
	IsHaveElectric = false;
	Timer = 0;
}

ElectricShockwaveBarrier::~ElectricShockwaveBarrier()
{
	delete animation;
}

int ElectricShockwaveBarrier::OnCollision(Entity *obj, float dt)
{
	if (!IsHaveElectric)
	{
		return 0;
	}
	if (obj->GetTag() != Entity::Entity_Tag::player)
	{
		return 0;
	}
	if (Player::GetInstance()->time_invisible > 0)
	{
		return 0;
	}
	if (Collision::getInstance()->IsCollide(obj->GetBoundingBox(), this->GetBoundingBox()))
	{
		Player::GetInstance()->ChangeState(new PlayerShockingState(PLAYER_HP));
	}
	return 0;
}

BoundingBox ElectricShockwaveBarrier::GetBoundingBox()
{
	if (!IsHaveElectric)
	{
		SIZE size;
		size.cx = 0;
		size.cy = 0;
		return BoundingBox(Entity::position, size, 0, 0);
	}
	return Entity::GetBoundingBox();
}

void ElectricShockwaveBarrier::Update(float dt)
{
	Timer += dt;
	if (Timer > ELECTRIC_SHOCKWAVE_BARRIER_TIME_CROSS)
	{
		IsHaveElectric = true;
		animation->Update(dt);
	}
	if (Timer > ELECTRIC_SHOCKWAVE_BARRIER_TIME_WAIT + ELECTRIC_SHOCKWAVE_BARRIER_TIME_CROSS)
	{
		Timer = 0;
		IsHaveElectric = false;
		animation->ResetAnimation();
	}
}

void ElectricShockwaveBarrier::Draw()
{
	if (IsHaveElectric)
	{
		animation->DrawInt(Entity::position);
	}
}
