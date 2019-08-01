#pragma once
#include <d3dx9.h>
#include <math.h>
#include "Entity.h"
class Equation
{
private:
	float a, b, c;
public:
	Equation(D3DXVECTOR2 point1, D3DXVECTOR2 point2);
	float GetYFromX(float x);
	Equation();
	~Equation();
};

class Eclipse {
private:
	float a, b;
	D3DXVECTOR2 center;
public:
	Eclipse(D3DXVECTOR2 point1, Entity::Entity_Direction direction, float distance);
	float GetYFromX(float x, int direction);
	Eclipse();
	~Eclipse();
};

