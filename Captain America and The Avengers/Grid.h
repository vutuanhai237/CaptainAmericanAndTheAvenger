#pragma once
#include <list>
#include <vector>
#include "Entity.h"
#include "Camera.h"

#define GRID_CELL_SIZE_WIDTH 40
#define GRID_CELL_SIZE_HEIGHT 80
#define CAPACITY_ITEM 3
#define CAPACITY_ENEMY 20

struct Cell
{
	bool IsActive;
	std::list<Entity*> *Object;
	std::vector<int*> *InitObject;
	Cell()
	{
		Object = new std::list<Entity*>();
		InitObject = new std::vector<int*>();
		IsActive = false;
	}
	~Cell()
	{
		Object->clear();
		InitObject->clear();
		delete Object;
		delete InitObject;
	}
};

class Grid
{
public:
	Grid(SIZE MapSize);
	Grid(int MapSizeWidth, int MapSizeHeight);
	~Grid();

	void AddObject2Cell(int WorldX, int WorldY, int *object);
	void AddObject2Cell(Entity *object);
	void Update(float dt);
	void DrawActivatedObject();

	int ItemCounter, EnemyCounter;
private:
	int CellX, CellY;
	Cell ***grid;

	int Xfrom, Xto, Yfrom, Yto;
	void Init(int MapSizeWidth, int MapSizeHeight);

	void UpdateActivatedZone();
	void RemoveAndReswampObject();
	void UpdateGrid();
	void CheckCollision(float dt);
	void UpdateEntity(float dt);

	bool IsActivated(int column, int row);
	void CollisionCall(std::list<Entity*> *ListObject1, std::list<Entity*> *ListObject2, float dt);
};