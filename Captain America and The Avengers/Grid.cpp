#include "Grid.h"
#include <math.h>
#include "RedRocketRobot.h"
#include "BlueSoldier.h"
#include "Player.h"
#include "Shield.h"

Grid::Grid(SIZE MapSize)
{
	Init(MapSize.cx, MapSize.cy);
}

Grid::Grid(int MapSizeWidth, int MapSizeHeight)
{
	Init(MapSizeWidth, MapSizeHeight);
}

Grid::~Grid()
{
	for (int i = 0; i < CellX; i++)
	{
		for (int j = 0; j < CellY; j++)
			delete grid[i][j];
		delete grid[i];
	}
	delete grid;
}

void Grid::AddObject2Cell(int WorldX, int WorldY, int* object)
{
	grid[WorldX / GRID_CELL_SIZE_WIDTH][WorldY / GRID_CELL_SIZE_HEIGHT]->InitObject->push_back(object);
}

void Grid::AddObject2Cell(Entity *object)
{ 
	int col = int(object->GetPosition().x / GRID_CELL_SIZE_WIDTH);
	int row = int(object->GetPosition().y / GRID_CELL_SIZE_HEIGHT);
	if (IsActivated(col, row))
		grid[col][row]->Object->push_back(object);
}

void Grid::Update(float dt)
{
	UpdateActivatedZone();
	RemoveAndReswampObject();
	UpdateGrid();
	CheckCollision(dt);
	UpdateEntity(dt);
}

void Grid::Init(int MapSizeWidth, int MapSizeHeight)
{
	CellX = (int)ceilf(float(MapSizeWidth + 1) / GRID_CELL_SIZE_WIDTH) + 1;
	CellY = (int)ceilf(float(MapSizeHeight + 1) / GRID_CELL_SIZE_HEIGHT) + 1;
	grid = new Cell**[CellX];
	for (int i = 0; i < CellX; i++)
	{
		grid[i] = new Cell*[CellY];
		for (int j = 0; j < CellY; j++)
			grid[i][j] = new Cell;
	}
	Player *player = Player::GetInstance();
	grid[int(player->GetPosition().x / GRID_CELL_SIZE_WIDTH)][int(player->GetPosition().y / GRID_CELL_SIZE_HEIGHT)]->Object->push_back(player);
	Shield *shield = Shield::GetInstance();
	grid[int(shield->GetPosition().x / GRID_CELL_SIZE_WIDTH)][int(shield->GetPosition().y) / GRID_CELL_SIZE_HEIGHT]->Object->push_back(shield);

	ItemCounter = 0;
	EnemyCounter = 0;

	Xfrom = Yfrom = 0;
	Xto = CellX - 1;
	Yto = CellY - 1;
}

void Grid::UpdateActivatedZone()
{
	D3DXVECTOR2 pos = Camera::GetInstance()->GetCameraPosition();
	Xfrom = floor((pos.x - 1) / GRID_CELL_SIZE_WIDTH);
	Xto = ceil((pos.x + 1 + GAME_SCREEN_WIDTH) / GRID_CELL_SIZE_WIDTH) + 1;
	Yfrom = floor(pos.y / GRID_CELL_SIZE_HEIGHT);
	Yto = ceil((pos.y + GAME_SCREEN_HEIGHT) / GRID_CELL_SIZE_HEIGHT);
	if (Xfrom < 0)
		Xfrom = 0;
	if (Xto >= CellX)
		Xto = CellX - 1;
}

void Grid::RemoveAndReswampObject()
{
	for (int i = 0; i < CellX; i++)
		for (int j = 0; j < CellY; j++)
			if (IsActivated(i, j))
			{
				if (!grid[i][j]->IsActive)
				{
					for (auto item : *grid[i][j]->InitObject)
						switch (item[0])
						{
						case Entity::Entity_Tag::redrobotrocket:
							if (this->EnemyCounter < CAPACITY_ENEMY) 
							{
								grid[i][j]->Object->push_back(new RedRocketRobot(item[3], D3DXVECTOR2(item[1], item[2]), D3DXVECTOR2(item[4], item[5]), item[6]));
								this->EnemyCounter++;
							}			
							break;
						case Entity::Entity_Tag::blue_soldier:
							if (this->EnemyCounter < CAPACITY_ENEMY)
							{
								grid[i][j]->Object->push_back(new BlueSoldier(item[3], D3DXVECTOR2(item[1], item[2]), item[4]));
								this->EnemyCounter++;
							}
							break;
						default:
							break;
						}
				}
				grid[i][j]->IsActive = true;
			}
			else
			{
				auto it = grid[i][j]->Object->begin();
				while (it != grid[i][j]->Object->end())
					if ((*it)->GetTag() == Entity::Entity_Tag::shield)
					{
						// shield exception
						D3DXVECTOR2 pos = (*it)->GetPosition(); 
						int LocX = pos.x / GRID_CELL_SIZE_WIDTH;
						int LocY = pos.y / GRID_CELL_SIZE_HEIGHT;
						if ((LocX != i || LocY != j) && 0 < LocX && LocX < CellX)
						{
							grid[LocX][LocY]->Object->push_back(*it);
							auto del = it;
							it++;
							grid[i][j]->Object->erase(del);
						}
					}
					else
						RemoveObjectInList(grid[i][j]->Object, it);
				grid[i][j]->IsActive = false;
			}
}

void Grid::UpdateGrid()
{
	D3DXVECTOR2 pos;
	int LocX, LocY;

	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
		{
			auto it = grid[i][j]->Object->begin();
			while (it != grid[i][j]->Object->end())
			{
				pos = (*it)->GetPosition();
				LocX = pos.x / GRID_CELL_SIZE_WIDTH;
				LocY = pos.y / GRID_CELL_SIZE_HEIGHT;
				if ((LocX != i || LocY != j) && 0 < LocX && LocX < CellX)
				{
					grid[LocX][LocY]->Object->push_back(*it);
					auto del = it;
					it++;
					grid[i][j]->Object->erase(del);
				}
				else
					it++;
			}
		}
}

void Grid::CheckCollision(float dt)
{
	int ret;

	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
		{
			auto objs = grid[i][j]->Object;
			// Check self cell
			if (objs->size() >= 2)
			{
				auto it_i = objs->begin();
				while (it_i != objs->end())
				{
					auto it_j = it_i;
					it_j++;
					while (it_j != objs->end())
					{
						ret = (*it_i)->OnCollision(*it_j, dt);
						if (ret == 1)
						{
							if (RemoveObjectInList(objs, it_i))
								goto CHECK_OTHER;
						}
						else if (ret == -1)
						{
							if (RemoveObjectInList(objs, it_j))
								break;
						}
						else
						{
							ret = (*it_j)->OnCollision(*it_i, dt);
							if (ret == -1)
							{
								if (RemoveObjectInList(objs, it_i))
									goto CHECK_OTHER;
							}
							else if (ret == 1)
							{
								if (RemoveObjectInList(objs, it_j))
									break;
							}
						}
						it_j++;
					}
					it_i++;
				}
			}
			// Check another cell
		CHECK_OTHER:
			if (!objs->empty())
			{
				if (i > 0)
				{
					CollisionCall(objs, grid[i - 1][j]->Object, dt);
					if (j < CellY - 1)
						CollisionCall(objs, grid[i - 1][j + 1]->Object, dt);
					if (j > 0)
						CollisionCall(objs, grid[i - 1][j - 1]->Object, dt);
				}
				if (j > 0)
					CollisionCall(objs, grid[i][j - 1]->Object, dt);
			}
		}
}

void Grid::UpdateEntity(float dt)
{
	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				if (obj->GetTag() != Entity::Entity_Tag::player && obj->GetTag() != Entity::Entity_Tag::shield)
					obj->Update(dt);
}

void Grid::DrawActivatedObject()
{
	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				if (obj->GetType() == Entity::Entity_Type::item_type)
					obj->Draw();

	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				if (obj->GetType() == Entity::Entity_Type::enemy_type)
					obj->Draw();

	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				if (obj->GetType() != Entity::Entity_Type::enemy_weapon_type && obj->GetType() != Entity::Entity_Type::enemy_type)
					obj->Draw();
			
}

bool Grid::IsActivated(int column, int row)
{
	return Xfrom <= column && column <= Xto && Yfrom <= row && row <= Yto;
}

void Grid::CollisionCall(std::list<Entity*> *ListObject1, std::list<Entity*> *ListObject2, float dt)
{
	int ret = 0;
	
	auto it_i = ListObject1->begin();
	while (it_i != ListObject1->end())
	{
		auto it_j = ListObject2->begin();
		while (it_j != ListObject2->end())
		{
			ret = (*it_i)->OnCollision(*it_j, dt);
			if (ret == 1) // remove it_i;
			{
				if (RemoveObjectInList(ListObject1, it_i))
					return;
				else
					goto ENDLOOP;
			}
			else if (ret == -1) // remove it_j
			{
				if (RemoveObjectInList(ListObject2, it_j))
					break;
				else
					continue;
			}
			else
			{
				ret = (*it_j)->OnCollision(*it_i, dt);
				if (ret == -1) // remove it_i;
				{
					if (RemoveObjectInList(ListObject1, it_i))
						return;
					else
						goto ENDLOOP;
				}
				else if (ret == 1) // remove it_j
				{
					if (RemoveObjectInList(ListObject2, it_j))
						break;
					else
						continue;
				}
			}
			it_j++;
		}
		it_i++;
	ENDLOOP:
		{}
	}
}

bool Grid::RemoveObjectInList(std::list<Entity*>* list, std::list<Entity*>::iterator &it)
{
	std::list<Entity*>::iterator del = it;
	it++;
	switch ((*del)->GetType())
	{
	case Entity::Entity_Type::player_type:
		goto UN_DELETE;
	case Entity::Entity_Type::item_type:
		if ((*del)->GetTag() == Entity::Entity_Tag::item_container)
			goto UN_DELETE;
		else
			this->ItemCounter--;
		break;
	case Entity::Entity_Type::enemy_type:
		this->EnemyCounter--;
		break;
	default:
		break;
	}
	delete (*del);
	list->erase(del);

UN_DELETE:

	if (it == list->end())
		return true;
	else
		return false;
}
