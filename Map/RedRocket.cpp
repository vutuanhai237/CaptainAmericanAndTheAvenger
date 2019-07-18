#include "RedRocket.h"



RedRocket::RedRocket()
{
	this->crossed_ani = new Animation(RedRocket::crossed, L"Resources//Enemy//RedRocketRobot//RedRocketCrossed.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	this->horizontal_ani = new Animation(RedRocket::horizontal, L"Resources//Enemy//RedRocketRobot//RedRocketHorizontal.png", D3DCOLOR_XRGB(255, 0, 255), 2);

}


RedRocket::~RedRocket()
{
}
