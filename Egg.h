#pragma once
#include <windows.h>

class Egg
{
public:
	Egg(int x = 0, int speed = 1);
	~Egg();

	_COORD GetPosition();
	_COORD GetPrevPosition();
	int GetSpeed();
	void move_down();
private:

	_COORD position;
	_COORD prev_position;
	int speed = 1;
};