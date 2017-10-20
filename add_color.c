#include "corewar.h"

void    add_color(int a, unsigned int champ, t_bs *bs)
{
    bs->color_map[a].champ = (char) champ;
    bs->color_map[a].cycle_n = g_count;
}