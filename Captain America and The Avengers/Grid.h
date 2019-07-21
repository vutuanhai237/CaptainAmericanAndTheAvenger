#pragma once
#include <list>
#include "Entity.h"
#include "Camera.h"
class Cell {
public:
	bool IsActive;
	D3DXVECTOR2 position;
	
};
class Grid
{
private:
	std::list<Entity*>** cells;
	int row;
	int col;
	float width;
	float height;
	float width_cell;
	float height_cell;
	
	D3DXVECTOR2 position_active_bot_left;
	D3DXVECTOR2 position_active_top_right;
public:
	void Add(Entity*entity);
	void UpdateActiveCells(float dt);
	void Remove(Entity*, float x, float y);
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

