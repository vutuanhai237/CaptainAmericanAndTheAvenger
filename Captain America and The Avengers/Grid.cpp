#include "Grid.h"
#include <math.h>

Grid::Grid(int MapSizeWidth, int MapSizeHeight)
{
	CellX = (int)floor((float)MapSizeWidth / GRID_CELL_SIZE);
	CellY = (int)floor((float)MapSizeHeight / GRID_CELL_SIZE);
	grid = new Cell**[CellX];
	for (int i = 0; i < CellX; i++)
	{
		grid[i] = new Cell*[CellY];
		for (int j = 0; j < CellY; j++)
			grid[i][j] = new Cell;
	}
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

void Grid::AddObject2Cell(int column, int row, Entity* object)
{
	grid[column][row]->InitObject->push_back(object);
}

void Grid::UpdateActivatedZone()
{
	RECT ActivatedBox = Camera::GetInstance()->GetCameraViewRect();
	Xfrom = (ActivatedBox.left - 1) / GRID_CELL_SIZE;
	Xto = (ActivatedBox.right + 1) / GRID_CELL_SIZE;
	Yfrom = ActivatedBox.bottom / GRID_CELL_SIZE;
	Yto = ActivatedBox.top / GRID_CELL_SIZE;
	if (Xfrom < 0)
		Xfrom = 0;
	if (Xto >= CellX)
		Xto = CellX - 1;
}

void Grid::UpdateGrid()
{
	D3DXVECTOR2 pos;
	int LocX, LocY;

	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			if (!grid[i][j]->Object->empty())
			{
				auto it = grid[i][j]->Object->begin();

				while (it != grid[i][j]->Object->end())
				{
					pos = (*it)->GetPosition();
					LocX = pos.x / GRID_CELL_SIZE;
					LocY = pos.y / GRID_CELL_SIZE;
					if (LocX != i || LocY != j)
					{
						AddObject2Cell(LocX, LocY, *it);
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
	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
		{
			// Check self cell
			if (!grid[i][j]->Object->empty())
			{
				auto it_i = grid[i][j]->Object->begin();
				while (it_i != grid[i][j]->Object->end())
				{
					auto it_j = it_i++;
					while (it_j != grid[i][j]->Object->end())
					{
						(*it_i)->OnCollision(*it_j, dt);
						(*it_j)->OnCollision(*it_i, dt);
						it_j++;
					}
					it_i++;
				}
			}
			// Check another cell
			if (i > 0)
			{
				CollisionCall(grid[i][j]->Object, grid[i - 1][j]->Object, dt);
				if (j < CellY - 1)
					CollisionCall(grid[i][j]->Object, grid[i - 1][j + 1]->Object, dt);
				if (j > 0)
					CollisionCall(grid[i][j]->Object, grid[i - 1][j - 1]->Object, dt);
			}
			else if (j > 0)
				CollisionCall(grid[i][j]->Object, grid[i][j - 1]->Object, dt);
		}
}

void Grid::UpdateEntity(float dt)
{
	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				obj->Update(dt);
}

void Grid::DrawActivatedObject()
{
	for (int i = Xfrom; i <= Xto; i++)
		for (int j = Yfrom; j <= Yto; j++)
			for (auto obj : *grid[i][j]->Object)
				obj->Draw();
}

void Grid::CollisionCall(std::list<Entity*>* ListObject1, std::list<Entity*>* ListObject2, float dt)
{
	for (auto obj1 : *ListObject1)
		for (auto obj2 : *ListObject2)
		{
			obj1->OnCollision(obj2, dt);
			obj2->OnCollision(obj1, dt);
		}
}