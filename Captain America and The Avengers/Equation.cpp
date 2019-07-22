#include "Equation.h"



Equation::Equation(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	float A = point1.x;
	float B = point1.y;
	float C = point2.x;
	float D = point2.y;
	// Giải phương trình
	this->a = (4 * B) / (9 * A*A - 6 * A*C + C * C - 16 * (B - 2 * D)*(B - 2 * D));
	this->b = this->a*(A - C);
	this->c = B - this->a*A*A - this->a*A*(A - C);

}

float Equation::GetYFromX(float x)
{
	return (a*x*x + b * x + c);
}

Equation::Equation()
{
	a = b = c = 0;
}


Equation::~Equation()
{
}
