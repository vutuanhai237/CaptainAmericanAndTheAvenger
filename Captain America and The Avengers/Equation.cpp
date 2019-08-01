#include "Equation.h"
#include "Framework/Debug.h"


Equation::Equation(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{

	float xA = point1.x;
	float yA = point1.y;
	float xB = point2.x;
	float yB = point2.y;
	float xC = (xA + xB) / 2;
	float yC = (2 * yB - yA); if (yC == yB) yC += 50;
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

Eclipse::Eclipse(D3DXVECTOR2 point1, Entity::Entity_Direction direction, float distance)
{
	this->center = point1;
	this->a = distance;
	this->b = distance * 0.5;
}

float Eclipse::GetYFromX(float x, int IsLui)
{
	float in_sqrt = (1 - (x)*(x) / (a*a))*b*b;
	float y = (sqrt(in_sqrt))*IsLui; 
	/*if (y > center.y + this->a / 2) {
		y = center.y + this->a / 2;
	}
	if (y < center.y - this->a / 2) {
		y = center.y - this->a / 2;
	}*/
	Debug::PrintOut(L"x = %f, y = %f\n", x, y);
	return y;
}

Eclipse::Eclipse()
{
	this->a = this->b = 0;
}

Eclipse::~Eclipse()
{
}
