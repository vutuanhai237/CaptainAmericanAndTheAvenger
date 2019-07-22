#pragma once
#include <list>
#include "Entity.h"
#include "Camera.h"

class Cell
{
public:
	bool IsActive;
	D3DXVECTOR2 position;
	std::list<Entity*> object;
};

class Grid
{
private:
	std::list<Entity*> **cells;
	int row;
	int col;
	float width;
	float height;
	float width_cell;
	float height_cell;
	
	D3DXVECTOR2 position_active_bot_left;
	D3DXVECTOR2 position_active_top_right;
public:
	void MoveLeft(Entity* entity);
	void MoveRight(Entity* entity);
	void MoveTop(Entity* entity);
	void MoveBot(Entity* entity);

	void Add(Entity*entity);
	void UpdateActiveCells(float dt);
	void Remove(Entity*entity, float x, float y);
	void Remove(Entity*entity);
	void UpdateActivedCells(float dt);
	void ClearOut(float dt);
	void Draw();
	float GetWidth();
	float GetHeight();
	int GetRow();
	int GetCol();
	Grid();
	Grid(float width, float height);
	~Grid();
};

