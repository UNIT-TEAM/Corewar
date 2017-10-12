#include "ncurs.h"
#include "unistd.h"
#include "../corewar.h"


t_cell    *make_body(int a)
{
    t_cell *body;
     a = 319;
    unsigned char b = 0;
    body = (t_cell *)malloc(sizeof(t_cell)*(a+1));
    while (a >= 0){
        body[a].cell = a;
        b++;
        body[a].champ = 1;
        if (a > 20)
            body[a].champ = 2;
        if (a > 50)
            body[a].champ = 3;
        a--;
    }
    return body;
}

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
        attron(COLOR_PAIR(champ * 100));
        y = base[(a / 16) % 16];
        mvwprintw(stdscr, starty, startx++, "%c", y);
        y = base[a % 16];
        mvwprintw(stdscr, starty, startx++, "%c", y);
        attroff(COLOR_PAIR(champ * 100));
        proc = proc->next;
    }
}
void draw_mass(t_bs *bs, int size)
{
    char const *base = "0123456789abcdef";
    int a = 0;
    int b = 0;
    int startx = 1;
    int starty = 1;
    while (b < size) {
        if (g_count - bs->color_map[b].cycle_n < 11) {
            char y;
            a = 0;
            while (a < 32) {
                attron(COLOR_PAIR(bs->color_map[b].champ));
                if (g_count - bs->color_map[b].cycle_n < 6)
                    attron(COLOR_PAIR(bs->color_map[b].champ * 10));
                y = base[(bs->map[b] / 16) % 16];
                mvwprintw(stdscr, starty, startx++, "%c", y);
                y = base[bs->map[b] % 16];
                mvwprintw(stdscr, starty, startx++, "%c", y);
                startx++;
                attroff(COLOR_PAIR(bs->color_map[b].champ));
                if (g_count - bs->color_map[b].cycle_n < 6)
                    attroff(COLOR_PAIR(bs->color_map[b].champ * 10));
                a++;
                b++;
            }
            starty++;
            startx = 1;
        }
        else
            b++;
    }
    draw_cart(bs);
}

void make_scene(t_ncurs *base, WINDOW *win, int d)
{
    int ch;

    int size = 320;
        init_win_params(win, size);
        create_box(win, size);
        ncurses_stats(win);
    draw_mass(base->mass, size);


    //timeout(0.5);
    //ch = getch();
//    switch(ch)
//        {	case KEY_F(2):
//               base->ready = 1;
//                break;
//            case KEY_F(3):
//                base->ready = -1;
//                break;
//        }

//    while((ch = getch()) != KEY_F(5))
//    {
//        switch(ch)
//        {	case KEY_F(2):
//               base->ready = 1;
//                break;
//            case KEY_F(3):
//                base->ready = -1;
//                break;
//        }
//        if (base->ready == 1 || base->ready == -1)
//            break;
//
//    }
    refresh();
    wrefresh(win);
    sleep(1);
    base->ready = 1;


}
void init_win_params(WINDOW *p_win, int size)
{
    p_win->_maxy = 40;
    p_win->_maxx = 160;
    p_win->_begx = 0;
    p_win->_begy = 0;
}
void create_box(WINDOW *p_win, int size)
{
    int x, y, w, h;

    x = p_win->_begx;
    y = p_win->_begy;
    w = p_win->_maxx;
    h = p_win->_maxy;

        mvwaddch(p_win,y, x, '+');
        mvwaddch(p_win,y, x + w, '+');
        mvwaddch(p_win,y + h, x, '+');
        mvwaddch(p_win,y + h, x + w, '+');
        mvwhline(p_win,y, x + 1,'-', w - 1);
        mvwhline(p_win,y + h, x + 1, '-', w - 1);
        mvwvline(p_win,y + 1, x, '|', h - 1);
        mvwvline(p_win,y + 1, x + w, '|', h - 1);
        mvwvline(p_win,y + 1, x + 98, '|', h - 1);
    refresh();
    wrefresh(p_win);
}

void ncurses_init_win(t_ncurs *base){
    initscr();
    WINDOW *window = newwin(66, 260,0,0);
    cbreak();
    start_color();
    ncurses_init_colors();
    noecho();
    init_win_params(window, 319);
    base->window = window;
}
int main() {
    t_ncurs *base = malloc(sizeof(t_ncurs));
    base->ready = 0;
    ncurses_init_win(base);
    int a = 0;
    int d = 1;
    base->mass = make_body(319);
    keypad(stdscr, TRUE);
    int cf;
    //TODO kbhit();
    while (1) {
        if (base->ready == -1)
            break;
        if (base->ready == 1) {
            base->mass[a].cell = 150;
            a++;
        }
        timeout(1);
        cf = getch();
        base->ready = 0;
        make_scene(base, base->window, d);

    }

    endwin();
}