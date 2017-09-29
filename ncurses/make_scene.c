#include <ncurses.h>
#include "stdlib.h"

typedef struct _win_border_struct {
    chtype 	ls, rs, ts, bs,
            tl, tr, bl, br;
}WIN_BORDER;


unsigned char    **make_body()
{
    unsigned char **body;
    int a = 9;
    int b;
    body = (unsigned char **)malloc(sizeof(unsigned char*)*(a+1));
    while (a >= 0){
        b = 9;
        body[a] = (unsigned char *)malloc(sizeof(unsigned char)*(b+1));
        while (b >= 0)
        {
            body[a][b] = 120;
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
void print_win_params(WIN *p_win);
void create_box(WIN *win, int size);

void draw_mass(unsigned char **mass, int size)
{
    char const *base = "0123456789abcdef";
    int a = 0;
    int b = 0;
    int startx = 1;
    int starty = 1;
    while (b < size) {
        char y = 97;
        a = 0;
        while (a < size) {
            y = base[(mass[b][a] / 16)%16];
            mvwprintw(stdscr, starty, startx++, "%s", &y);
            y = base[mass[b][a] % 16];
            mvwprintw(stdscr, starty, startx++, "%s", &y);
            y++;
            mvwprintw(stdscr, starty, startx, " ");
            startx++;
            a++;
        }
        b++;
        starty++;
        startx = 1;
    }
}
void make_scene(unsigned char **mass)
{
    WIN win;
    int ch;

    int size = 10;

    initscr();
    if (LINES < 15 || COLS < 15)
    {
        printf("malo suka\n");
        printf("lines = %d\n", LINES);
        printf("cols = %d\n", COLS);
        endwin();
        exit(0);
    }
    start_color();
   // cbreak();
    /* Line buffering disabled, Pass on
					 * everty thing to me 		*/
    keypad(stdscr, TRUE);
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_GREEN);

    init_win_params(&win, size);
    print_win_params(&win);

    create_box(&win, size);
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, 5, 1, "%s", "h");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, 5, 2, "%s", "Y");
    attroff(COLOR_PAIR(2));
    draw_mass(mass, size);
    while((ch = getch()) != KEY_F(2)){
//    {	switch(ch)
//        {	case KEY_LEFT:
//                create_box(&win, FALSE);
//                --win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_RIGHT:
//                create_box(&win, FALSE);
//                ++win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_UP:
//                create_box(&win, FALSE);
//                --win.starty;
//                create_box(&win, TRUE);
//                break;
//            case KEY_DOWN:
//                create_box(&win, FALSE);
//                ++win.starty;
//                create_box(&win, TRUE);
//                break;
//        }


    }

    endwin();			/* End curses mode		  */
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
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
				p_win->width, p_win->height);
	refresh();
#endif
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
int main()
{
    make_scene(make_body());
}