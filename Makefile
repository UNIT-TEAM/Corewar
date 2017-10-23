all:
	gcc add_color.c champion.c fill_bot.c instruct.c main.c ncurses/make_scene.c ./ncurses/ncurses_init_colors.c ./ncurses/ncurses_stats.c ./ncurses/proc_key.c check_op_h.c map.c map1.c map2.c libft/libft.a op.c st_ld.c add_or_zjump_fork_aff.c for_instruct_and_live.c del_base_to_zero_error.c flags.c -lncurses
