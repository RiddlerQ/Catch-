#include "Bowl.h"
#include <windows.h>
#include <iostream>

Bowl::Bowl(int width, int bowl_size) : bowl_size(bowl_size)
{
	if (bowl_size >= 1)
	{
		position_left = width/2 - bowl_size/2;
		position_right = width/2 + bowl_size/2;

		if (bowl_size % 2 == 0)
			position_right -= 1;
	}
	else
	{
		std::cout << "ERROR.01 -> Bowl has to be bigger then 0 \n";
		exit(1);
	}
}

Bowl::~Bowl()
{

}

void Bowl::move_left()
{
	if (position_left > 2)
	{
		position_left -= 1;
		position_right -= 1;
	}
}

void Bowl::move_right(int width)
{
	if (position_right < width-2)
	{
		position_left += 1;
		position_right += 1;
	}
}