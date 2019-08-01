#include "PittsburghMap.h"
#include "OnOffSwitch.h"
#include "Door.h"
#include "DisappearPlatform.h"
#include "MovingPlatform.h"
#include "CrossPlatform.h"
#include "CirclePlatform.h"
#include "Player.h"
#include "Shield.h"
#include <fstream>
#include "Camera.h"

PittsburghMap::PittsburghMap()
{
	map = new std::vector<WorldMap*>();
	grid = new std::vector<Grid*>();
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_dark_map.txt", 0));
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_light_map.txt", 0));
	grid->push_back(new Grid((*map)[map->size() - 1]->GetMapSize()));
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_dark_map_portal_1.txt", 0));
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_light_map_portal_1.txt", 0));
	grid->push_back(new Grid((*map)[map->size() - 1]->GetMapSize()));
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_dark_map_portal_2.txt", 0));
	map->push_back(new WorldMap(L"Resources/Map/pittsburgh_light_map_portal_2.txt", 0));
	grid->push_back(new Grid((*map)[map->size() - 1]->GetMapSize()));

	Mode = MapMode::Dark;
	ReadData(L"Resources/Map/pittsburgh_item_enemy.txt", 0);
	ReadData(L"Resources/Map/pittsburgh_portal_1_item_enemy.txt", 1);
}

void PittsburghMap::SwapMode()
{
	Mode = Mode ^ 1;
}

void PittsburghMap::SwapMap(int map)
{
	Mode = map << 1 | Mode & 1;
	if (Mode >> 1 > 0)
	{
		Camera::GetInstance()->SetCameraPosition(0, 0);
		Camera::GetInstance()->SetCameraFreeze(true);
	}
	else
	{
		Camera::GetInstance()->SetCameraFreeze(false);
		Camera::GetInstance()->RefreshCamera(Player::GetInstance()->GetPosition());
	}
}

int PittsburghMap::GetMapMode()
{
	return Mode;
}

WorldMap *PittsburghMap::GetCurrentMap()
{
	return (*map)[Mode];
}

Grid *PittsburghMap::GetCurrentGrid()
{
	return (*grid)[Mode >> 1];
}

SIZE PittsburghMap::GetMapSize()
{
	return (*map)[Mode]->GetMapSize();
}

void PittsburghMap::ReadData(LPCWSTR path, int code)
{
	int n;
	int tag, posX, posY, tmp;
	Entity *item;
	int *obj;

	fstream data(path, ios_base::in);
	data >> n;

	for (int i = 0; i < n; i++)
	{
		data >> tag >> posX >> posY;
		switch (tag)
		{
		case Entity::Entity_Tag::on_off_switch:
			item = new OnOffSwitch(posX, posY);
			(*grid)[code]->AddObject2Cell(item);
			break;
		case Entity::Entity_Tag::door:
			obj = new int[3];
			data >> obj[0] >> obj[1] >> obj[2];
			item = new Door(posX, posY, obj[0], obj[1], obj[2]);
			(*grid)[code]->AddObject2Cell(item);
			delete obj;
			break;
		case Entity::Entity_Tag::disappear_platform:
			item = new DisappearPlatform(posX, posY);
			(*grid)[code]->AddObject2Cell(item);
			break;
		case Entity::Entity_Tag::moving_platform:
			obj = new int;
			data >> *obj;
			item = new MovingPlatform(posX, posY, *obj);
			(*grid)[code]->AddObject2Cell(item);
			break;
		case Entity::Entity_Tag::cross_platform:
			obj = new int;
			data >> *obj;
			item = new CrossPlatform(posX, posY, *obj);
			(*grid)[code]->AddObject2Cell(item);
			break;
		case Entity::Entity_Tag::circle_platform:
			obj = new int[3];
			data >> obj[0] >> obj[1]>>obj[2];
			item = new CirclePlatform(posX, posY, obj[0], obj[1], obj[2]);
			(*grid)[code]->AddObject2Cell(item);
			break;
		default:
			break;
		}
	}

	(*grid)[code]->AddObject2Cell(Player::GetInstance());
	(*grid)[code]->AddObject2Cell(Shield::GetInstance());
}

PittsburghMap::~PittsburghMap()
{
	for (WorldMap *item : *map)
		delete item;
	map->clear();
	delete map;
	for (Grid *item : *grid)
		delete item;
	grid->clear();
	delete grid;
}

void PittsburghMap::Draw()
{
	(*map)[Mode]->Draw();
}