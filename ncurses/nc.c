#include <ncurses.h>

//typedef struct _win_border_struct {
//    chtype 	ls, rs, ts, bs,
//            tl, tr, bl, br;
//}WIN_BORDER;
//
//typedef struct _WIN_struct {
//
//    int startx, starty;
//    int height, width;
//    WIN_BORDER border;
//}WIN;
//
//void init_win_params(WIN *p_win);
//void print_win_params(WIN *p_win);
//void create_box(WIN *win, bool flag);
//
//int main(int argc, char *argv[])
//{	WIN win;
//    int ch;
//
//    initscr();			/* Start curses mode 		*/
//    start_color();			/* Start the color functionality */
//   // cbreak();
//    /* Line buffering disabled, Pass on
//					 * everty thing to me 		*/
//    keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
//    noecho();
//    init_pair(1, COLOR_CYAN, COLOR_BLACK);
//    init_pair(2, COLOR_RED, COLOR_GREEN);
//
//    /* Initialize the window parameters */
//    init_win_params(&win);
//    print_win_params(&win);
//
//    attron(COLOR_PAIR(2));
//    printw("Press F1 to exit");
//    refresh();
//    attroff(COLOR_PAIR(1));
//
//    create_box(&win, TRUE);
//    while((ch = getch()) != KEY_F(1))
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
//    }
//    endwin();			/* End curses mode		  */
//    return 0;
//}
//void init_win_params(WIN *p_win)
//{
//    p_win->height = 3;
//    p_win->width = 10;
//    p_win->starty = (LINES - p_win->height)/2;
//    p_win->startx = (COLS - p_win->width)/2;
//    //printf("lines = %d\n", LINES);
//
//    p_win->border.ls = '|';
//    p_win->border.rs = '|';
//    p_win->border.ts = '-';
//    p_win->border.bs = '-';
//    //p_win->border.tl = '+';
//    p_win->border.tl = LINES+48;
//    p_win->border.tr = '+';
//    p_win->border.bl = '+';
//    p_win->border.br = '+';
//
//}
//void print_win_params(WIN *p_win)
//{
//#ifdef _DEBUG
//    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
//				p_win->width, p_win->height);
//	refresh();
//#endif
//}
//void create_box(WIN *p_win, bool flag)
//{	int i, j;
//    int x, y, w, h;
//
//    x = p_win->startx;
//    y = p_win->starty;
//    w = p_win->width;
//    h = p_win->height;
//
//    if(flag == TRUE)
//    {	mvaddch(y, x, p_win->border.tl);
//        mvaddch(y, x + w, p_win->border.tr);
//        mvaddch(y + h, x, p_win->border.bl);
//        mvaddch(y + h, x + w, p_win->border.br);
//        mvhline(y, x + 1, p_win->border.ts, w - 1);
//        mvhline(y + h, x + 1, p_win->border.bs, w - 1);
//        mvvline(y + 1, x, p_win->border.ls, h - 1);
//        mvvline(y + 1, x + w, p_win->border.rs, h - 1);
//
//    }
//    else
//        for(j = y; j <= y + h; ++j)
//            for(i = x; i <= x + w; ++i)
//                mvaddch(j, i, ' ');
//
//    refresh();
//
//}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
int main(int argc, char *argv[])
{	initscr();			/* Start curses mode 		*/
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();			/* Start color 			*/
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);


    attron(COLOR_PAIR(2));
    print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
    attroff(COLOR_PAIR(2));

    getch();
    endwin();
}
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{	int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    mvwprintw(win, 0, 0, "%s", string);
    refresh();
}