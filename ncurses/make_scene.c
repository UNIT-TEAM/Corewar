#include "ncurs.h"

typedef struct _win_border_struct {
    chtype 	ls, rs, ts, bs,
            tl, tr, bl, br;
}WIN_BORDER;


t_cell    **make_body()
{
    t_cell **body;
    int a = 9;
    int b;
    body = (t_cell **)malloc(sizeof(t_cell*)*(a+1));
    while (a >= 0){
        b = 9;
        body[a] = (t_cell *)malloc(sizeof(t_cell)*(b+1));
        while (b >= 0)
        {
            body[a][b].cell = 120;
            body[a][b].champ = 1;
            if (a >= 5)
                body[a][b].champ = 2;
            if (a == 9)
                body[a][b].champ = 0;
            b--;
        }
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

void draw_mass(t_cell **mass, int size)
{
    char const *base = "0123456789abcdef";
    int a = 0;
    int b = 0;
    int startx = 1;
    int starty = 1;
    while (b < size) {
        char y;
        a = 0;
        while (a < size) {
            attron(COLOR_PAIR(mass[b][a].champ));
            y = base[(mass[b][a].cell / 16)%16];
            mvwprintw(stdscr, starty, startx++, "%s", &y);
            y = base[mass[b][a].cell % 16];
            mvwprintw(stdscr, starty, startx++, "%s", &y);
            y++;
            mvwprintw(stdscr, starty, startx, " ");
            startx++;
            attroff(COLOR_PAIR(mass[b][a].champ));
            a++;

        }
        b++;
        starty++;
        startx = 1;
    }
}
void make_scene(t_ncurs *base, WIN win)
{
    int ch;

    int size = 10;
    if (LINES < 15 || COLS < 15)
    {
        printf("malo suka\n");
        printf("lines = %d\n", LINES);
        printf("cols = %d\n", COLS);
        endwin();
        exit(0);
    }
    keypad(stdscr, TRUE);
    noecho();
    init_win_params(&win, size);


    create_box(&win, size);
    draw_mass(base->mass, size);
    while((ch = getch()) != KEY_F(5))
    {	switch(ch)
        {	case KEY_F(2):
               base->ready = 1;
                break;
            case KEY_F(3):
                base->ready = -1;
                break;
        }
        if (base->ready == 1 || base->ready == -1)
            break;

    }

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
    int win_s = (size * 3) + 2;

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
        mvvline(y + 1, x + win_s, p_win->border.ls, h - 1);
    refresh();

}
int main() {
    WIN win;
    initscr();
    start_color();
    ncurses_init_colors();
    t_ncurs *base = malloc(sizeof(t_ncurs));
    base->ready = 1;
    int a = 0;
    base->mass = make_body();
    while (1) {
        if (base->ready == -1)
            break;
        if (base->ready == 1) {
            base->mass[0][a].cell = 150;
            a++;
        }
        base->ready = 0;
        make_scene(base, win);

    }

    endwin();
}