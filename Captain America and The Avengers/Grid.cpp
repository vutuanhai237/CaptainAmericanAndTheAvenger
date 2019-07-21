#include "Grid.h"

void Grid::Add(Entity *entity)
{
	int col = entity->GetPosition().x / width_cell;
	int row = entity->GetPosition().y / height_cell;
	this->cells[col][row].push_back(entity);
}

void Grid::UpdateActiveCells(float dt)
{
	Camera* camera = Camera::GetInstance();
	int x_position_of_cell_bot_left_active = camera->GetCameraPosition().x / width_cell + 1;
	int y_position_of_cell_bot_left_active = camera->GetCameraPosition().y / height_cell + 1;
	this->position_active_bot_left = D3DXVECTOR2(x_position_of_cell_bot_left_active, y_position_of_cell_bot_left_active);
	int x_position_of_cell_top_right_active = (camera->GetCameraPosition().x + this->width) / width_cell;
	int y_position_of_cell_top_right_active = (camera->GetCameraPosition().y + this->height) / height_cell;
	this->position_active_top_right = D3DXVECTOR2(x_position_of_cell_top_right_active, y_position_of_cell_top_right_active);
}
void Grid::Remove(Entity *, float x, float y)
{

}

void Grid::UpdateActivedCells(float dt)
{
	for (int i = 1; i <= position_active_bot_left.x; i++) {
		for (int j = 1; j <= position_active_top_right.x; j++) {
			for (auto object : this->cells[i][j]) {
				object->Update(dt);
			}
		}
	}
}

void Grid::ClearOut(float dt)
{
	for (int i = 1; i <= this->col; i++) {
		if (i < position_active_bot_left.x && i > position_active_top_right.x) {
			for (int j = 1; j <= this->row; j++) {
				if (j < position_active_bot_left.y && j > position_active_top_right.y) {


					// Clear here
					for (auto object : this->cells[i][j]) {
						
					}
				}	
			}
		}
	
	}
}

void Grid::Draw()
{
}

float Grid::GetWidth()
{
	return this->width;
}

float Grid::GetHeight()
{
	return this->height;
}

int Grid::GetRow()
{
	return this->row;
}

int Grid::GetCol()
{
	return this->col;
}

Grid::Grid()
{
	for (int i = 1; i <= this->col; i++) {
		for (int j = 1; j <= this->row; j++) {

		}
	}
}

Grid::Grid(float width, float height)
{
	Camera *camera = Camera::GetInstance();
	this->width = width;
	this->height = height;
	this->col = this->width / this->width_cell;
	this->row = this->height / this->height_cell;
	for (int i = 1; i <= this->col; i++) {
		this->cells = new std::list<Entity*>*[i];
		for (int j = 1; j <= this->row; j++)
		{
			cells[i] = new std::list<Entity*>[j];
		}		
	}
}


Grid::~Grid()
{
	for (int i = 1; i <= this->col; i++) {
		this->cells = new std::list<Entity*>*[i];
		for (int j = 1; j <= this->row; j++)
		{
			cells[i] = new std::list<Entity*>[j];
		}
	}
}
