#include "Barrel.h"
#include "FrameWork//Debug.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
#include "Shield.h"
void Barrel::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->current_ani->Update(dt);

	if (this->IsExploding) {
		this->Exploding(dt);
		return;
	}

	if (this->IsCollisionWithWall(dt).CollisionTime < 1.0f) {
		this->Release();
		this->IsExploding = true;
	}
	this->time_wait += dt;
	if (this->time_wait >= 1.0) {
		this->SetVelocityX(distance_out*1.5);
		if (this->e != NULL) {
			this->SetPositionY(this->e->GetYFromX(this->GetPosition().x));
		}
	}
	

	this->distance += abs(this->GetVelocityX()*dt);

}

int Barrel::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) {
		return 1;
	}
	BossGragas* boss = BossGragas::GetInstance();
	if (obj->GetType() == Entity::Entity_Type::player_weapon_type)
	{
		if (Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox())) {
			if (obj->GetTag() == Entity::Entity_Tag::shield) {
				if (this->GetVelocityX() == 0) {
					goto CHECK;
				}
				else {
					if (this->IsExploding == false) {
						this->Release();
						this->IsExploding = true;
					}
				}
			}
			else {
				// PUNCH - KICH
				CHECK:
				if (this->IsExploding == false) {
					this->Release();
					this->IsExploding = true;
					boss->count_barrel_explode++;
					boss->phase = 0;
					boss->count_bullet = 0;
					boss->time_throwing = 0;
				}
				
			}

		
		}

	}
	Player *player = Player::GetInstance();
	if (obj->GetType() != Entity::Entity_Type::player_type)
		return 0;
	if (player->time_invisible <= 0
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		player->ChangeState(new PlayerBeatenState(BARREL_DAMAGE));
		if (this->IsExploding == false) {
			this->Release();
			this->IsExploding = true;
		}
	}
	return 0;

}

void Barrel::Exploding(float dt)
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

void Barrel::Release()
{
	this->distance = 0;
	this->IsStraight = true;
	this->time_out_straight = 0;
	this->time_out_explode = 0;
}

void Barrel::Draw()
{
	this->current_ani->Draw(this->GetPosition());
	if (this->GetMoveDirection()) {
		this->current_ani->SetScale(1, 1);
	}
	else {
		this->current_ani->SetScale(-1, 1);
	}
	

}

Barrel::Barrel(D3DXVECTOR2 position, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::red_rocket);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->explode_ani = new Animation(7, 3);
	this->explode_ani->SetTime(0.083, 10000);
	this->current_ani = new Animation(29, 1);
	this->size.cx = 13; this->size.cy = 13;
	this->SetPosition(position);
	this->IsDead = false;
	this->time_out_straight = 0;
	this->IsLocking = true;
	this->IsExploding = false;
	this->SetVelocityX(0);
	this->SetMoveDirection(direction);
	this->damage = BARREL_DAMAGE;
	this->time_wait = 0;
	BossGragas* boss = BossGragas::GetInstance();
	this->distance_out = abs(boss->GetPosition().x - Player::GetInstance()->GetPosition().x);
	if (distance_out < 10) { distance_out = 10; };
	if (distance_out > 50) { distance_out = 50; };

	this->e = new Equation(
		this->position,	D3DXVECTOR2(
			this->position.x + (boss->GetMoveDirection() == Entity::Entity_Direction::RightToLeft ? -1 : 1) * distance_out,
			this->position.y + 20
		)
	);

}

CollisionOut Barrel::IsCollisionWithWall(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BARREL_SIZE_WIDTH;
	FootSize.cy = BARREL_SIZE_HEIGHT;
	int direction_x = BossGragas::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	int direction_y = BossGragas::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop ? 1 : -1;

	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, abs(velocity.x*dt)*direction_x, abs(velocity.y)*dt*direction_y);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::wall)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			switch (tmp.side)
			{
			case CollisionSide::bottom:
				if (BossGragas::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop) {
					continue;
				}
				position.y = item->GetPosition().y + (BOSS_GRAGAS_SIZE_HEIGHT + item->GetSize().cy) / 2 - delta_y;
				velocity.y = 0;
				return tmp;
			case CollisionSide::left:
				position.x = item->GetPosition().x + (BOSS_GRAGAS_SIZE_WIDTH + item->GetSize().cx) / 2 + 2;
				velocity.x = 0;
				return tmp;
			case CollisionSide::right:
				position.x = item->GetPosition().x - (BOSS_GRAGAS_SIZE_WIDTH + item->GetSize().cx) / 2 - 2;
				velocity.x = 0;
				return tmp;
			default:
				continue;
			}
		}
	}
	return tmp;
}


Barrel::~Barrel()
{
}


