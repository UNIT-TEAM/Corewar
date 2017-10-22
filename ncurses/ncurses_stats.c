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

void    ncurses_result(t_ncurs *base, t_bs *bs)
{
    t_chmp *chmp;
    char *name;
    int col;

    chmp = bs->list_champs;
    while (chmp)
    {
        if (chmp->num == bs->winner)
        {
            name = chmp->head.prog_name;
            col = chmp->num;
        }
        chmp = chmp->next;
    }

    base->b += 2;
    mvwprintw(base->window, base->b, base->a, "The winner is : ");
    attron(COLOR_PAIR(col));
    mvwprintw(base->window, base->b, base->a + 19, "%s", name);
    base->b += 2;
    attroff(COLOR_PAIR(col));
    mvwprintw(base->window, base->b, base->a, "Press any key to finish");

}
void    ncurses_stats(WINDOW *window, t_ncurs *base, t_bs *bs){
    base->a = 206;
    base->b = 2;
    t_chmp *chmps;

    chmps = bs->list_champs;
    if (!base->flag)
        mvwprintw(window, base->b++, base->a, "%s","** PAUSED **");
    else
        mvwprintw(window, base->b++, base->a, "%s","** RUNING **");
    mvwprintw(window, base->b, base->a, "%s","Cycles/second limit :");
    mvwprintw(window, base->b++, base->a + 25, "%d     ", base->n_cyc);
    base->b += 2;
    mvwprintw(window, base->b, base->a, "%s","Cycle :");
    mvwprintw(window, base->b++, base->a + 10, "%d", g_count);
    base->b++;
    mvwprintw(window, base->b, base->a, "%s","Processes :");
    mvwprintw(window, base->b++, base->a + 15, "%d", proc_count(bs));
    base->b++;

    while (chmps)
    {
        mvwprintw(window, base->b, base->a,"Player -%d :", chmps->num);
        attron(COLOR_PAIR(chmps->num));
        mvwprintw(window, base->b++, base->a + 15, "%s", chmps->head.prog_name);
        attroff(COLOR_PAIR(chmps->num));
        mvwprintw(window, base->b++, base->a,"Last live :                 %d", chmps->cycle_live);
        mvwprintw(window, base->b++, base->a,"Lives in curent period :   %d        ", chmps->live);
        base->b++;
        chmps = chmps->next;
    }
    mvwprintw(window, base->b++, base->a, "CYCLES TO DIE : %d   ", base->cyc_to_die);
    base->b++;
    mvwprintw(window, base->b++, base->a, "CYCLE_DELTA : %d   ", CYCLE_DELTA);
    base->b++;
    mvwprintw(window, base->b++, base->a, "NBR_LIVE : %d   ", NBR_LIVE);
    base->b++;
    mvwprintw(window, base->b++, base->a, "MAX_CHECKS : %d   ", MAX_CHECKS);

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