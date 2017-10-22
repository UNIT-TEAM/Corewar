#include "unistd.h"
#include "../corewar.h"

void init_win_params(WINDOW *p_win, int size);
void create_box(WINDOW *win, int size);


void draw_cart(t_bs *bs)
{
    t_proc *proc;
    char const *base;
    unsigned int a;
    unsigned int champ;
    char y;

    base = "0123456789abcdef";
    proc = bs->list_proc;
    while (proc)
    {
        a = proc->pc;
        champ = proc->id;
        if (bs->color_map[a].champ == 0)
            attron(COLOR_PAIR(100));
        else
            attron(COLOR_PAIR(proc->id + 100));
        y = base[(bs->map[a] / 16) % 16];
        mvwprintw(stdscr, a/64 + 2, (a%64)*3 + 2, "%c", y);
        y = base[bs->map[a] % 16];
        mvwprintw(stdscr, a/64 + 2, (a%64)*3 + 1 + 2, "%c", y);
        if (bs->color_map[a].champ == 0)
            attroff(COLOR_PAIR(100));
        else
            attroff(COLOR_PAIR(proc->id + 100));
        bs->color_map[a].carretka = 1;
        proc = proc->next;
    }
}
int     find_color(t_bs *bs, int a)
{
    if (bs->color_map[a].carretka == 1 && bs->color_map[a].champ == 0)
        return (0);
    if (g_count - bs->color_map[a].cycle_n < 6 &&  bs->color_map[a].cycle_n != 0)
        return (bs->color_map[a].champ * 10);
    return (bs->color_map[a].champ);
}
void draw_mass(t_bs *bs, int size)
{
    char const *base = "0123456789abcdef";
    int a = 0;
    int b = 0;
    int startx = 2;
    int starty = 2;
    while (b < size) {

            char y;
            a = 0;
            while (a < 64) {
//               if (g_count - bs->color_map[b].cycle_n < 11 || g_count == 0 || bs->color_map[b].carretka == 1)
//                {
//                    attron(COLOR_PAIR(bs->color_map[b].champ));
//                    if (g_count - bs->color_map[b].cycle_n < 6 &&  bs->color_map[b].cycle_n != 0)
//                        attron(COLOR_PAIR(bs->color_map[b].champ * 10));
                    attron(COLOR_PAIR(find_color(bs, b)));
                    y = base[(bs->map[b] / 16) % 16];
                    mvwprintw(stdscr, starty, startx++, "%c", y);
                    y = base[bs->map[b] % 16];
                    mvwprintw(stdscr, starty, startx++, "%c", y);
                    startx++;
//                    attroff(COLOR_PAIR(bs->color_map[b].champ+1));
//                    if (g_count - bs->color_map[b].cycle_n < 6)
//                        attroff(COLOR_PAIR(bs->color_map[b].champ * 10));
                    attroff(COLOR_PAIR(find_color(bs, b)));
                    a++;
                    b++;
                    bs->color_map[b].carretka = 0;
//                }
//                else
//                {
//                    a++;
//                    b++;
//                    startx = startx + 3;
//                }
            }
            starty++;
            startx = 2;

    }

   draw_cart(bs);
}
//void make_scene(t_ncurs *base, WINDOW *win, int d)
//{
//    int ch;
//
//    int size = 4096;
//        init_win_params(win, size);
//        create_box(win, size);
//        ncurses_stats(win, base);
//    draw_mass(base->mass, size);
//
//    refresh();
//    wrefresh(win);
//    //sleep(1);
//    base->ready = 1;
//
//
//}
void init_win_params(WINDOW *p_win, int size)
{
//    p_win->_maxy = 40;
//    WINDOW *dd;
//    p_win->_maxx = 160;
//    p_win->_begx = 0;
//    p_win->_begy = 0;
}
void create_box(WINDOW *p_win, int size)
{
    int x, y, w, h;

//    x = p_win->_begx;
//    y = p_win->_begy;
//    w = p_win->_maxx;
//    h = p_win->_maxy;
    x = 0;
    y = 0;
    w = 265;
    h = 68;

    int starty;
    starty = 0;
    int startx;
    startx = 1;
    attron(COLOR_PAIR(111));
//    while (startx < w) {
//
//        mvwprintw(stdscr, starty, startx++, "%c", 'f');
//
//    }
        mvwaddch(stdscr,y, x, '+');
        mvwaddch(stdscr,y, x + w, '+');
        mvwaddch(stdscr,y + h, x, '+');
        mvwaddch(stdscr,y + h, x + w, '+');
        mvwhline(stdscr,y, x + 1,'-', w - 1);
        mvwhline(stdscr,y + h, x + 1, '-', w - 1);
        mvwvline(stdscr,y + 1, x, '|', h - 1);
        mvwvline(stdscr,y + 1, x + w, '|', h - 1);
        mvwvline(stdscr,y + 1, x + 200, '|', h - 1);
    attroff(COLOR_PAIR(111));

    refresh();
    wrefresh(p_win);
}

void ncurses_init_win(t_ncurs *base){
    initscr();
   // WINDOW *window = newwin(100, 350,0,0);
    cbreak();
    start_color();
    ncurses_init_colors();
    noecho();
    //init_win_params(window, 4095);
    base->n_cyc = 10;
    base->flag = 0;
    base->window = stdscr;
}
void ncurs_start(t_bs *bs) {
//    t_ncurs *base = malloc(sizeof(t_ncurs));
//    base->ready = 0;
//    ncurses_init_win(base);
//    int a = 0;
//    base->mass = make_body(bs);
//    keypad(stdscr, TRUE);
//    int cf;
    //kbhit();
//    while (1) {
//        if (base->ready == -1)
//            break;
//        if (base->ready == 1) {
//            base->mass[a].cell = 150;
//            a++;
//        }
//        timeout(1);
//        cf = getch();
//        base->ready = 0;
//        make_scene(base, base->window, 1);
//
//    }
//
//    endwin();
}