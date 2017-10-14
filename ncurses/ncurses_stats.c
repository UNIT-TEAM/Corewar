#include "../corewar.h"

int     proc_count(t_bs *bs)
{
    t_proc *proc;
    int      a;

    proc = bs->list_proc;
    a = 0;
    while (proc)
    {
        a++;
        proc = proc->next;
    }
    return a;
}

void    stats2(WINDOW *window, t_ncurs *base, t_bs *bs, int b)
{
    int a;

    a = 206;
    mvwprintw(window, b, a, "%s","Processes :");
    mvwprintw(window, b++, a + 15, "%d", proc_count(bs));
    b++;
    while (chmps)
    {
        mvwprintw(window, b, a,"Player -%d :", chmps->num);
        attron(COLOR_PAIR(chmps->num));
        mvwprintw(window, b++, a + 15, "%s", chmps->head.prog_name);
        attroff(COLOR_PAIR(chmps->num));
        mvwprintw(window, b++, a,"Last live :                 %d", chmps->num);
        mvwprintw(window, b++, a,"Lives in curesnt period :   %d", chmps->live);
        b++;
        chmps = chmps->next;
    }
    mvwprintw(window, b++, a, "CYCLES TO DIE : %d", CYCLE_TO_DIE);
    b++;
    mvwprintw(window, b++, a, "CYCLE_DELTA : %d", CYCLE_DELTA);
    b++;
    mvwprintw(window, b++, a, "NBR_LIVE : %d", NBR_LIVE);
    b++;
    mvwprintw(window, b++, a, "MAX_CHECKS : %d", MAX_CHECKS);
}
void    ncurses_stats(WINDOW *window, t_ncurs *base, t_bs *bs)
{
    int a;
    int b;
    t_chmp *chmps;

    a = 206;
    b = 2;
    chmps = bs->list_champs;
    if (!base->flag)
        mvwprintw(window, b++, a, "%s","** PAUSED **");
    else
        mvwprintw(window, b++, a, "%s","** RUNING **");
    mvwprintw(window, b, a, "%s","Cycles/second limit :");
    mvwprintw(window, b++, a + 25, "%d", base->n_cyc);
    b += 2;
    mvwprintw(window, b, a, "%s","Cycle :");
    mvwprintw(window, b++, a + 10, "%d", g_count);
    b++;
   stats2(window, base, bs, b);
}