#pragma once
#include <list>
#include <vector>
#include "Entity.h"
#include "Camera.h"

#define GRID_CELL_SIZE 80

struct Cell
{
	bool IsActive;
	std::list<Entity*> *Object;
	std::vector<Entity*> *InitObject;
	Cell()
	{
		Object = new std::list<Entity*>();
		InitObject = new std::vector<Entity*>();
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
	Grid(int MapSizeWidth, int MapSizeHeight);
	~Grid();

	void AddObject2Cell(int column, int row, Entity* object);

	void UpdateActivatedZone();
	void UpdateGrid();
	void CheckCollision(float dt);
	void UpdateEntity(float dt);
	void DrawActivatedObject();
private:
	int CellX, CellY;
	Cell ***grid;

	int Xfrom, Xto, Yfrom, Yto;
	void CollisionCall(std::list<Entity*> *ListObject1, std::list<Entity*> *ListObject2, float dt);
};