#include <iostream>
#include "../header/Game.h"

int main()
{

    int num_eggs = 5; 
    int bowl_size = 5;
    int width = 50;
    int heigh = 30;

    Game a(num_eggs, bowl_size, width, heigh);

    a.start();
}