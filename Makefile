GCC =       gcc -Wall -Wextra -Werror
NAME =      corewar

FILES = corewar_vm/add_color.o\
        corewar_vm/add_or_zjump_fork_aff.o\
        corewar_vm/champion.o\
        corewar_vm/check_num_atoi.o\
        corewar_vm/check_op_h.o\
        corewar_vm/del_base_to_zero_error.o\
        corewar_vm/fill_bot.o\
        corewar_vm/flags.o\
        corewar_vm/for_instruct_and_live.o\
        corewar_vm/take_args.o\
        corewar_vm/main.o\
        corewar_vm/map.o\
        corewar_vm/map1.o\
        corewar_vm/map2.o\
        corewar_vm/op.o\
        corewar_vm/st_ld.o\
        ncurses/make_scene.o\
        ncurses/ncurses_init_colors.o\
        ncurses/ncurses_stats.o\
        ncurses/proc_key.o

all: $(NAME)

$(NAME) : libft.a $(FILES)
	@ $(GCC) $(FILES) -o $(NAME) ./libft/libft.a -lncurses
	@ echo "\033[32mcorewar was compiled \033[0m"
	@ make -C ./dasm
	@ cp dasm/asm ./asm

libft.a:
	@ make -C ./libft
	@ echo "\033[32mlibft.a was compiled \033[0m"

%.o: %.c
	@ gcc -o $@ -c $< -I . -I ./libft

clean:
	@ rm -rf $(FILES)
	@ make clean -C ./libft
	@ echo "\033[31mrm -rf *o\033[0m"
	@ make clean -C ./dasm

fclean: clean
	@ rm -rf $(NAME)
	@ rm -rf ./libft/libft.a
	@ make fclean -C ./dasm
	@ rm asm

re: fclean all
