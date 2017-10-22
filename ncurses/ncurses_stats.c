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

void    ncurses_stats(WINDOW *window, t_ncurs *base, t_bs *bs){
    int a = 206;
    int b = 2;
    t_chmp *chmps;

    chmps = bs->list_champs;
    if (!base->flag)
        mvwprintw(window, b++, a, "%s","** PAUSED **");
    else
        mvwprintw(window, b++, a, "%s","** RUNING **");
    mvwprintw(window, b, a, "%s","Cycles/second limit :");
    mvwprintw(window, b++, a + 25, "%d     ", base->n_cyc);
    b += 2;
    mvwprintw(window, b, a, "%s","Cycle :");
    mvwprintw(window, b++, a + 10, "%d", g_count);
    b++;
    mvwprintw(window, b, a, "%s","Processes :");
    mvwprintw(window, b++, a + 15, "%d", proc_count(bs));
    b++;

    while (chmps)
    {
        mvwprintw(window, b, a,"Player -%d :", chmps->num);
        attron(COLOR_PAIR(chmps->num));
        mvwprintw(window, b++, a + 15, "%s", chmps->head.prog_name);
        attroff(COLOR_PAIR(chmps->num));
        mvwprintw(window, b++, a,"Last live :                 %d", chmps->cycle_live);
        mvwprintw(window, b++, a,"Lives in curent period :   %d        ", chmps->live);
        b++;
        chmps = chmps->next;
    }
    mvwprintw(window, b++, a, "CYCLES TO DIE : %d   ", base->cyc_to_die);
    b++;
    mvwprintw(window, b++, a, "CYCLE_DELTA : %d   ", CYCLE_DELTA);
    b++;
    mvwprintw(window, b++, a, "NBR_LIVE : %d   ", NBR_LIVE);
    b++;
    mvwprintw(window, b++, a, "MAX_CHECKS : %d   ", MAX_CHECKS);

//    mvwprintw(window, b++, a, "%s","Cycles/second limit");
//    mvwprintw(window, 5, a, "%s","g_count");
//    mvwprintw(window, 5, a + 9, "%d", g_count);
//    mvwprintw(window, 6, a, "%s","n_cyc");
//    mvwprintw(window, 6, a + 9, "%d", base->n_cyc);
//    mvwprintw(window, 7, a, "%s","carry");
//    mvwprintw(window, 7, a + 9, "%d", bs->list_proc->carry);
//    int a = 8;
//    while (a < 25) {
//        mvwprintw(window, a, a, "%s", "reg");
//        mvwprintw(window, a, a + 9, "%u", bs->list_proc->regs[a-8]);
//        a++;
//    }

}