#include "Equation.h"



Equation::Equation(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{

	float xA = point1.x;
	float yA = point1.y;
	float xB = point2.x;
	float yB = point2.y;
	float xC = (xA + xB) / 2;
	float yC = (2 * yB - yA); if (yC == yB) yC += 60;
	// Giải phương trình
	this->a = ((yA - yB) / (xA - xB) - (yA - yC) / (xA - xC)) / (xB - xC);
	this->b = (yA - yB) / (xA - xB) - this->a*(xA + xB);
	this->c = yA - a * xA * xA - b * xA;

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
