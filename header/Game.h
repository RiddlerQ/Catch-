#pragma once
#include "Bowl.h"
#include "Egg.h"
#include <vector>
#include <windows.h>
#include <mutex>

class Game : private Bowl
{
public:
	Game(int num_eggs = 5, int bowl_size = 5, int width = 70, int heigh = 50);
	~Game();

	void start();

private:
	void game_loop();
	void move_left();
	void move_right();
	void update_bowl();
	void update_egg();
	void update_score();

	bool mutex_flag = true;
	_COORD win_size;
	_SMALL_RECT rect;
	long long score = 0;
	int num_eggs = 5;
	int bowl_size = 5;
	std::vector<Egg> eggs;
	HANDLE handle;


};