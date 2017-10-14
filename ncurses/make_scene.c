#include "unistd.h"
#include "../corewar.h"
const char *g_base = "0123456789abcdef";
void create_box(WINDOW *p_win, int size)
{
    int w;
    int h;

    w = 265;
    h = 68;
    attron(COLOR_PAIR(111));
    mvwaddch(stdscr,0, 0, '+');
    mvwaddch(stdscr,0, w, '+');
    mvwaddch(stdscr,h, 0, '+');
    mvwaddch(stdscr,0 + h, w, '+');
    mvwhline(stdscr,0, 1,'-', w - 1);
    mvwhline(stdscr,h, 1, '-', w - 1);
    mvwvline(stdscr,1, 0, '|', h - 1);
    mvwvline(stdscr,1, w, '|', h - 1);
    mvwvline(stdscr,1, 200, '|', h - 1);
    attroff(COLOR_PAIR(111));
    refresh();
    //  wrefresh(p_win);
}

void draw_cart(t_bs *bs, t_proc *proc)
{
    unsigned int a;
    unsigned int champ;
    char y;

    while (proc)
    {
        a = proc->pc;
        champ = proc->id;
        attron(COLOR_PAIR(proc->id + 100));
        y = g_base[(bs->map[a] / 16) % 16];
        mvwprintw(stdscr, a/64 + 2, (a%64)*3 + 2, "%c", y);
        y = g_base[bs->map[a] % 16];
        mvwprintw(stdscr, a/64 + 2, (a%64)*3 + 1 + 2, "%c", y);
        attroff(COLOR_PAIR(proc->id + 100));
        proc = proc->next;
        bs->color_map[a].carretka = 1;
        if (g_count == 25)
            beep();
    }
}

int     find_color(t_bs *bs, int b)
{
    if (g_count - bs->color_map[b].cycle_n < 6 &&  bs->color_map[b].cycle_n != 0)
        return (bs->color_map[b].champ * 10);
    return (0);
}
void draw_mass(t_bs *bs, int a, int b)
{
    while (b < MEM_SIZE) {
            char y;
            a = 0;
            while (a < 64) {
                if (g_count - bs->color_map[b].cycle_n <1 || g_count == 0 ||bs->color_map[b].carretka == 1)
                {
                    attron(COLOR_PAIR(find_color(bs, b)));
                    y = g_base[(bs->map[b] / 16) % 16];
                    mvwprintw(stdscr, starty, bs->startx++, "%c", y);
                    y = g_base[bs->map[b] % 16];
                    mvwprintw(stdscr, starty, bs->startx++, "%c", y);
                    bs->startx++;
                    attroff(COLOR_PAIR(find_color(bs, b)));
                    bs->color_map[b].carretka = 0;
                }
                else
                    bs->startx += 3;
                a++;
                b++;
            }
            bs->starty++;
            bs->startx = 2;
    }
   draw_cart(bs, bs->list_proc);
}

void ncurses_init_win(t_ncurs *base){
    initscr();
    cbreak();
    start_color();
    ncurses_init_colors();
    noecho();
    base->n_cyc = 10;
    base->flag = 0;
    base->window = stdscr;
    base->startx = 2;
    base->starty = 2;
}
