#pragma once
#include "WorldMap.h"
#include "Grid.h"
#include <vector>

class PittsburghMap
{
public:
	PittsburghMap();
	~PittsburghMap();

	enum MapMode
	{
		Dark = 0,			// 000
		Light = 1,			// 001
		DarkPortal1 = 2,	// 010
		LightPortal1 = 3,	// 011
		DarkPortal2 = 4,	// 100
		LightPortal2 = 5	// 110
	};

	void Draw();
	void SwapMode(); // dark/light
	void SwapMap(int map); // map, portal1, portal2

	int GetMapMode(); 
	WorldMap *GetCurrentMap();
	Grid *GetCurrentGrid();
	SIZE GetMapSize();
private:
	std::vector<WorldMap*> *map;
	std::vector<Grid*> *grid;
	int Mode;

	void ReadData(LPCWSTR path, int code);
};

