#include "Game.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>

#define KEY_LEFT 75
#define KEY_RIGHT 77

Game::Game(int num_eggs, int bowl_size, int width, int heigh) : Bowl(width, bowl_size), num_eggs(num_eggs), bowl_size(bowl_size)
{
	srand(time(NULL));

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = heigh-1;
	rect.Right = width-1;

	win_size.X = width;
	win_size.Y = heigh;

	HWND ConsoleWindow = GetConsoleWindow();
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!handle || handle == INVALID_HANDLE_VALUE)
		exit(1);

	SetConsoleWindowInfo(handle, TRUE, &rect);
	SetConsoleScreenBufferSize(handle, win_size);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &cursorInfo);

	SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	for (size_t i = 0; i < num_eggs; i++)
	{
		bool unique = false;
		int rand_pos;
		while (unique == false)
		{
			rand_pos = rand() % win_size.X + 1;
			unique = true;

			for (auto& different_eggs : eggs)
			{
				if (rand_pos == different_eggs.GetPosition().X)
				{
					unique = false;
					break;
				}
			}
		}
		eggs.push_back(Egg(rand_pos, rand() % 2 + 1));
	}
}

Game::~Game()
{
}

void Game::start()
{
	update_bowl();
	update_score();
	std::vector<std::thread> egg_threads;

	std::thread a(&Game::update_egg, this);
	std::thread b(&Game::game_loop, this);
//	b.detach();
	game_loop();
}

void Game::game_loop()
{
	int c = 0;

	while (TRUE)
	{
		switch ((c = _getch())) 
		{
			case KEY_LEFT:
				mutex_flag = false;
				move_left();
				mutex_flag = true;
					break;

			case KEY_RIGHT:
				mutex_flag = false;
				move_right();
				mutex_flag = true;
					break;

			default:
				break;
		}
	}
}

	
void Game::move_left()
{
	Bowl::move_left();
	update_bowl();
}

void Game::move_right()
{
	Bowl::move_right(win_size.X);
	update_bowl();

}

void Game::update_bowl()
{
	_COORD a;
	a.X = position_left-1;
	a.Y = win_size.Y - 3;

	SetConsoleCursorPosition(handle, a);

	std::cout << ' ';

	for (size_t i = 0; i < bowl_size; i++)
	{
		std::cout << '~';
	}

	std::cout << ' ';

	a.X = position_left - 2;
	a.Y = win_size.Y - 4;

	SetConsoleCursorPosition(handle, a);

	std::cout << ' ' << "\\" << ' ';

	a.X = position_right;
	a.Y = win_size.Y - 4;

	SetConsoleCursorPosition(handle, a);
	std::cout << ' ' << '/' << ' ';

}

void Game::update_egg()
{
	long delay = 0;
	while (true)
	{
		delay += 1;
		if (delay >= 200000000 && mutex_flag == true)
		{
			for (auto& egg : eggs)
			{
				_COORD current_pos = egg.GetPosition();
				int speed = egg.GetSpeed();

				if (current_pos.Y >= win_size.Y - 3)
				{
					bool unique = false;
					int rand_pos;
					while (unique == false)
					{
						rand_pos = rand() % win_size.X + 1;
						unique = true;

						for (auto& different_eggs : eggs)
						{
							if (rand_pos == different_eggs.GetPosition().X)
							{
								unique = false;
								break;
							}
						}
					}


					egg = Egg(rand_pos, rand() % 2 + 1);

					current_pos.Y -= speed;
					while (mutex_flag == false) {};
					SetConsoleCursorPosition(handle, current_pos);
					{
						std::cout << ' ';
					}
				}
				else
				{
					while (mutex_flag == false) {};
					SetConsoleCursorPosition(handle, current_pos);
					std::cout << '#';

					while (mutex_flag == false) {};
					SetConsoleCursorPosition(handle, egg.GetPrevPosition());
					std::cout << ' ';

					egg.move_down();
				}

				current_pos = egg.GetPosition();

				if (current_pos.X > position_left - 1 && current_pos.X < position_right + 1 && current_pos.Y >= win_size.Y - 3)
				{
					score += 1;
				}

			}
			update_score();
			delay = 0;
		}
	}
}

void Game::update_score()
{
	_COORD pos_zero;
	pos_zero.X = 0;
	pos_zero.Y = 0;

	SetConsoleCursorPosition(handle, pos_zero);
	std::cout << "SCORE: " << score;

}

