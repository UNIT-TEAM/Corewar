cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses")

set(SOURCE_FILES corewar_vm/main.c corewar.h ./libft/libft.h op.h corewar_vm/fill_bot.c corewar_vm/map.c corewar_vm/map1.c
		corewar_vm/map2.c corewar_vm/for_instruct_and_live.c corewar_vm/add_or_zjump_fork_aff.c
		corewar_vm/champion.c corewar_vm/instruct.c corewar_vm/st_ld.c corewar_vm/op.c corewar_vm/check_op_h.c ./ncurses/make_scene.c
		./ncurses/ncurses_init_colors.c ./ncurses/ncurses_stats.c
		./ncurses/proc_key.c corewar_vm/add_color.c corewar_vm/map1.c corewar_vm/map2.c corewar_vm/flags.c
		corewar_vm/del_base_to_zero_error.c corewar_vm/check_num_atoi.c)
add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)