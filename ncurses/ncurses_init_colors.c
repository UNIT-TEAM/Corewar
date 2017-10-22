#include "../corewar.h"

void    ncurses_init_colors()
{

    init_pair(1, 2, 0); //green
    init_pair(2, 4, 0); //blue
    init_pair(3, 1, 0); // red
    init_pair(4, 6, 0); //cyan
    init_pair(5, 3, 0); //yellow
    init_pair(10, 82, 0);
    init_pair(20, 33, 0);
    init_pair(30, 197, 0);
    init_pair(40, 194, 0);
    init_pair(50, 11, 0);
    init_pair(101,  0,2);
    init_pair(102,  0,4);
    init_pair(103, 0,1);
    init_pair(104, 0,6);
    init_pair(105, 0,3);



    init_pair(111, 8, 8);
    init_pair(112, 8, 0);
}

//void    ncurses_init_colors()
//{
//
//    init_pair(1, COLOR_GREEN, COLOR_BLACK);
//    init_pair(2, COLOR_RED, COLOR_BLACK);
//    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
//    init_pair(4, COLOR_BLUE, COLOR_BLACK);
//    init_pair(10, COLOR_GREEN, COLOR_BLACK);
//    init_pair(20, COLOR_RED | COLOR_BLUE, COLOR_BLACK);
//    init_pair(30, COLOR_MAGENTA | COLOR_RED, COLOR_BLACK);
//    init_pair(40,  COLOR_BLUE | COLOR_GREEN, COLOR_BLACK);
//    init_pair(100,  COLOR_WHITE,COLOR_GREEN);
//    init_pair(200,  COLOR_WHITE, COLOR_RED);
//    init_pair(300, COLOR_WHITE,COLOR_MAGENTA);
//    init_pair(400, COLOR_WHITE,COLOR_BLUE);
//
//
//
//
//
//
//
//    init_pair(111, COLOR_WHITE, COLOR_BLACK|COLOR_WHITE);
//    init_pair(112, COLOR_BLACK|COLOR_WHITE, COLOR_BLACK);
//}
//gcc add_color.c champion.c map.c fill_bot.c instruct.c main.c op.c sti_ldi.c ncurses/ncurses_stats.c ncurses/ncurses_init_colors.c ncurses/make_scene.c ncurses/proc_key.c libft/libft.a -lncurses

//void draw_mass(t_bs *bs, int size)
//{
//    char const *base = "0123456789abcdef";
//    int a = 0;
//    int b = 0;
//    int startx = 2;
//    int starty = 2;
//    while (b < size) {
//        if (g_count - bs->color_map[b].cycle_n < 11) {
//            char y;
//            a = 0;
//            while (a < 64) {
//                attron(COLOR_PAIR(bs->color_map[b].champ+1));
//                if (g_count - bs->color_map[b].cycle_n < 6)
//                    attron(COLOR_PAIR(bs->color_map[b].champ * 10));
//                y = base[(bs->map[b] / 16) % 16];
//                mvwprintw(stdscr, starty, startx++, "%c", y);
//                y = base[bs->map[b] % 16];
//                mvwprintw(stdscr, starty, startx++, "%c", y);
//                startx++;
//                attroff(COLOR_PAIR(bs->color_map[b].champ+1));
//                if (g_count - bs->color_map[b].cycle_n < 6)
//                    attroff(COLOR_PAIR(bs->color_map[b].champ * 10));
//                a++;
//                b++;
//            }
//            starty++;
//            startx = 2;
//        }
//        else
//            b++;
//    }
//
////   draw_cart(bs);
//}