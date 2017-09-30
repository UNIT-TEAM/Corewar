//
// Created by ysavenko on 30.09.17.
//

#ifndef COREWAR_NCURS_H
#define COREWAR_NCURS_H

#include <ncurses.h>
#include "stdlib.h"

typedef struct      s_cell
{
    unsigned char   cell;
    int             champ;
    int             modif;
}                   t_cell;
typedef struct		s_ncur
{
   t_cell           **mass;
   int              ready;

}                   t_ncurs;

void    ncurses_init_colors();

#endif //COREWAR_NCURS_H
