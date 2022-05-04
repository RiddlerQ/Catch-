#include "../header/Egg.h"

Egg::Egg(int x, int speed): speed(speed)
{
	position.X = x;
	position.Y = 0;
}

Egg::~Egg()
{

}

_COORD Egg::GetPosition()
{
	return position;
}


_COORD Egg::GetPrevPosition()
{
	return prev_position;
}

int Egg::GetSpeed()
{
	return speed;
}

void Egg::move_down()
{
	prev_position = position;
	position.Y += speed;
}