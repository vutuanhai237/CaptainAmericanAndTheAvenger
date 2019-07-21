#pragma once
#include <d3dx9.h>
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

