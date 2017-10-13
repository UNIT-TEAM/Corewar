#include <ncurses.h>

int
main()
{
    initscr();
    cbreak();
    noecho();
   scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    int ch;
    while (true) {
//        if (getch() == 'g') {
//            printw("You pressed G\n");
//        }
        ch = getch();
        printf("%d\n", ch);
        napms(500);
        printw("Running\n");
    }
}