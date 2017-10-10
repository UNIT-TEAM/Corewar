#include "ncurs.h"
#include "unistd.h"

typedef struct _win_border_struct {
    chtype 	ls, rs, ts, bs,
            tl, tr, bl, br;
}WIN_BORDER;


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
typedef struct _WIN_struct {

    int startx, starty;
    int height, width;
    WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win, int size);
void create_box(WIN *win, int size);


void draw_mass(t_cell *mass, int size)
{
    char const *base = "0123456789abcdef";
    int a = 0;
    int b = 0;
    int startx = 1;
    int starty = 1;
    while (b < size) {
        char y;
        a = 0;
        while (a < 32) {
            attron(COLOR_PAIR(mass[b].champ));
            y = base[(mass[b].cell / 16)%16];
            mvwprintw(stdscr, starty, startx++, "%c", y);
            y = base[mass[b].cell % 16];
            mvwprintw(stdscr, starty, startx++, "%c", y);

            startx++;
            attroff(COLOR_PAIR(mass[b].champ));
            a++;
            b++;
        }
        starty++;
        startx = 1;
    }
}
void make_scene(t_ncurs *base, WIN *win, int d)
{
    int ch;

    int size = 320;
    if (d==1) {
//        if (LINES < 15 || COLS < 15) {
//            printf("malo suka\n");
//            printf("lines = %d\n", LINES);
//            printf("cols = %d\n", COLS);
//            endwin();
//            exit(0);
//        }

        noecho();
        init_win_params(win, size);
        create_box(win, size);
    }
    keypad(stdscr, TRUE);
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
    sleep(1);

    base->ready = 1;


}
void init_win_params(WIN *p_win, int size)
{
    p_win->height = size + 1;
    p_win->width = COLS - 1;
    p_win->starty = 0;
    p_win->startx = 0;

    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';
}
void create_box(WIN *p_win, int size)
{	int i, j;
    int x, y, w, h;
    //int win_s = (size * 3) + 2;


    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;

        mvaddch(y, x, p_win->border.tl);
        mvaddch(y, x + w, p_win->border.tr);
        mvaddch(y + h, x, p_win->border.bl);
        mvaddch(y + h, x + w, p_win->border.br);
        mvhline(y, x + 1, p_win->border.ts, w - 1);
        mvhline(y + h, x + 1, p_win->border.bs, w - 1);
        mvvline(y + 1, x, p_win->border.ls, h - 1);
        mvvline(y + 1, x + w, p_win->border.rs, h - 1);
        mvvline(y + 1, x + 98, p_win->border.ls, h - 1);
    refresh();
}

//write_l("enter to render_init");
//initscr();
//start_color();
//render_init_pair();
//d->window = newwin(MAP_HEIGHT, MAP_WIDTH, 0, 0);
//wbkgd(d->window, COLOR_PAIR(0));
//cbreak();
//noecho();
//nodelay(stdscr, true);
//curs_set(0);
//wrefresh(d->window);
//d->ncurse_speed = TIME_USLEEP;
//return (0);

int main() {
   // WIN *win;
    WINDOW *window = newwin(50, 50,0,0);
    initscr();
    win = newwin(0,0,0,0);
//    win.height = 50;
//    win.width = 50;
    start_color();
    ncurses_init_colors();
    t_ncurs *base = malloc(sizeof(t_ncurs));
    base->ready = 0;
    int a = 0;
    int d = 1;
    base->mass = make_body(319);
    while (1) {
        if (base->ready == -1)
            break;
        if (base->ready == 1) {
            base->mass[a].cell = 150;
            a++;
        }

        base->ready = 0;
        make_scene(base, win, d);
        if (d == 1)
            d = 0;
    }
    endwin();
}