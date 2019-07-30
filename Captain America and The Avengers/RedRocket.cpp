#include "RedRocket.h"
#include "FrameWork//Debug.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
void RedRocket::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->current_ani->Update(dt);

	if (this->IsExploding) {
		this->Exploding(dt);
		return;
	}
	
	if (this->distance > DISTANCE_OUT || EnemyWeapon::IsCollisionExplode()) {
		this->Release();
		this->IsExploding = true;
	}
	
	if (IsCrossed) {
		
		if (IsStraight) {
			this->current_ani = this->horizontal_ani;
			this->time_out_straight += dt;
			if (this->time_out_straight >= TIME_OUT_STRAIGHT) {
				IsStraight = false;
			}
		}
		else {
			this->position.y += abs(this->GetVelocityX()*dt);
			this->current_ani = this->crossed_ani;
		}
	}
	else {
	
	}
	this->distance += abs(this->GetVelocityX()*dt);

}

int RedRocket::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) {
		return 1;
	}
	Player *player = Player::GetInstance();
	if (obj->GetType() != Entity::Entity_Type::player_type)
		return 0;
	if (player->time_invisible <= 0
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		player->ChangeState(new PlayerBeatenState(RED_ROCKET_DAMAGE));
		if (this->IsExploding == false) {
			this->Release();
			this->IsExploding = true;
		}
	}
	return 0;

}

void RedRocket::Exploding(float dt)
{
	this->SetVelocityX(1);
	if (this->time_out_explode == 0) {
		this->current_ani = this->explode_ani;
	}
	this->time_out_explode += dt;
	if (this->time_out_explode > TIME_EXPLODE) {
		this->IsDead = true;
	}

}

void RedRocket::Release() 
{
	this->distance = 0;
	this->IsStraight = true;
	this->time_out_straight = 0;
	this->time_out_explode = 0;
}

void RedRocket::Draw()
{
	
	if (this->GetVelocityX() != 0) {
		this->current_ani->Draw(this->GetPosition());
		if (this->GetMoveDirection()) {
			this->current_ani->SetScale(1, 1);
		}
		else {
			this->current_ani->SetScale(-1, 1);
		}
	}
	
}

RedRocket::RedRocket(D3DXVECTOR2 position, bool IsCrossed, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::red_rocket);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->crossed_ani = new Animation(RedRocket::RedRocketState::crossed, 2);
	this->horizontal_ani = new Animation(RedRocket::RedRocketState::horizontal, 2);
	this->explode_ani = new Animation(RedRocket::RedRocketState::explode, 3); 
	this->explode_ani->SetTime(0.083, 10000);
	this->current_ani = this->horizontal_ani;
	this->SetVelocityX(5);
	this->size.cx = 13; this->size.cy = 5;
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsStraight = true;
	this->IsDead = false;
	this->time_out_straight = 0;
	this->IsCrossed = IsCrossed;
	this->IsExploding = false;
	this->SetVelocityX(RED_ROCKET_VELOCITY_X);
	this->SetMoveDirection(direction);
	this->damage = RED_ROCKET_DAMAGE;
}


RedRocket::~RedRocket()
{
	delete this->crossed_ani;
	delete this->horizontal_ani;
}
