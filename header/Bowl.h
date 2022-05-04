#pragma once

class Bowl
{
protected:
	Bowl(int width, int bowl_size = 5);
	virtual ~Bowl();
	virtual void move_left();
	virtual void move_right(int width);
	int bowl_size = 5;
	int position_left;
	int position_right;

};