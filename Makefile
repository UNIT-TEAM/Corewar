all:
	gcc add_color.c champion.c fill_bot.c instruct.c main.c ncurses/make_scene.c ./ncurses/ncurses_init_colors.c ./ncurses/ncurses_stats.c ./ncurses/proc_key.c check_op_h.c map.c libft/libft.a op.c sti_ldi.c -lncurses
