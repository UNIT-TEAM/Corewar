#include "../corewar.h"

void    ncurses_init_colors()
{
    init_pair(1, 1, 0);
    init_pair(2, 2, 0);
    init_pair(3, 3, 0);
    init_pair(4, 4, 0);
    init_pair(5, 5, 0);
    init_pair(6, 6, 0);
    init_pair(7, 9, 0);
    init_pair(8, 8, 0);
    init_pair(10, 0, 1);
    init_pair(20, 0, 2);
    init_pair(30, 0, 3);
    init_pair(40,  0, 4);
    init_pair(50, 0, 5);
    init_pair(60, 0, 6);
    init_pair(70, 0, 9);
    init_pair(80,  0, 8);
    init_pair(101,  1,COLOR_WHITE);
    init_pair(102,  2,COLOR_WHITE);
    init_pair(103, 3,COLOR_WHITE);
    init_pair(104, 4,COLOR_WHITE);
    init_pair(105,  5,COLOR_WHITE);
    init_pair(106,  6,COLOR_WHITE);
    init_pair(107, 9,COLOR_WHITE);
    init_pair(108, 8,COLOR_WHITE);
    init_pair(111, COLOR_WHITE, COLOR_BLACK|COLOR_WHITE);
    init_pair(112, COLOR_BLACK|COLOR_WHITE, COLOR_BLACK);
}
