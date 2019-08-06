#include "GrayRocket.h"
#include "Framework/GameSetting.h"
#include "Framework/SoundManager.h"
#include "PlayerBeatenState.h"

int GrayRocket::ID = -1;

float TrueRadian(float radian)
{
	while (radian < 0)
		radian += 2 * PI;
	while (radian > 2 * PI)
		radian -= 2 * PI;
	return radian;
}

GrayRocket::GrayRocket(FLOAT WorldX, FLOAT WorldY, Entity::Entity_Direction direction) : EnemyWeapon()
{
	// Animation zone
	this->current_ani = new Animation(GrayRocket::ID, 2);
	this->current_ani->SetTime(0.125f);
	this->explode_ani = new Animation(7, 3);
	this->explode_ani->SetTime(0.083f, 10000.0f);
	//
	Entity::position.x = WorldX;
	Entity::position.y = WorldY;
	if (direction == Entity::Entity_Direction::LeftToRight)
	{
		radian = 0;
	}
	else
	{
		radian = PI;
	}
	Timer = 0.0f;
	ChangeDirectionCounter = 7;
	this->time_out_explode = 0.0f;
	this->size.cx = 8; this->size.cy = 8;
	this->IsExploding = false;
	this->IsDead = false;
}

GrayRocket::~GrayRocket()
{
}

void GrayRocket::Update(float dt)
{
	Timer += dt;
	this->current_ani->Update(dt);
	if (this->IsExploding) 
	{
		this->Exploding(dt);
		return;
	}

	if (EnemyWeapon::IsCollisionExplode())
	{
		this->Release();
		this->IsExploding = true;
		SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
	}

	D3DXVECTOR2 target = Player::GetInstance()->GetPosition();
	if (ChangeDirectionCounter > 0 && Timer > GRAY_ROCKET_TIME_CHANGE_DIRECTION)
	{
		Timer -= GRAY_ROCKET_TIME_CHANGE_DIRECTION;
		float dx = target.x - Entity::position.x;
		float dy = target.y - Entity::position.y;
		if (sqrt(dx*dx + dy * dy) < GRAY_ROCKET_MIN_LOCATION_FOLLOW)
		{
			ChangeDirectionCounter = 0;
		}
		else
		{
			float direction = atan2f(dy, dx);
			float tmp1 = TrueRadian(direction - radian);
			float tmp2 = TrueRadian(radian - direction);
			if (tmp1 < tmp2)
			{
				if (tmp1 > GRAY_ROCKET_TURN / 2)
				{
					radian = TrueRadian(radian + GRAY_ROCKET_TURN);
					ChangeDirectionCounter--;
				}
			}
			else
			{
				if (tmp2 > GRAY_ROCKET_TURN / 2)
				{
					radian = TrueRadian(radian - GRAY_ROCKET_TURN);
					ChangeDirectionCounter--;
				}
			}
			this->current_ani->SetRotation(-radian);
		}
	}
	Entity::position.x += cosf(radian)*GRAY_ROCKET_VELOCITY*dt;
	Entity::position.y += sinf(radian)*GRAY_ROCKET_VELOCITY*dt;
}

int GrayRocket::OnCollision(Entity *obj, float dt)
{
	if (this->IsDead == true) 
	{
		return 1;
	}
	
	if (obj->GetType() != Entity::Entity_Type::player_type)
	{
		return 0;
	}

	Player *player = Player::GetInstance();
	if (player->time_invisible <= 0	&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		player->ChangeState(new PlayerBeatenState(GRAY_ROCKET_DAME));
		if (this->IsExploding == false)
		{
			this->Release();
			this->IsExploding = true;
			SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
		}
	}
	return 0;
}

void GrayRocket::Exploding(float dt)
{
	this->SetVelocityX(1);
	if (this->time_out_explode == 0) 
	{
		this->current_ani = this->explode_ani;
	}
	this->time_out_explode += dt;
	if (this->time_out_explode > TIME_EXPLODE) 
	{
		this->IsDead = true;
		this->OnCollision(NULL, dt);
	}
}

void GrayRocket::Draw()
{
	if (IsDead == false)
	{
		this->current_ani->Draw(Entity::position);
	}
}

void GrayRocket::Release()
{
	this->time_out_explode = 0;
}