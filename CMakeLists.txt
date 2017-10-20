cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses")

set(SOURCE_FILES main.c corewar.h ./libft/libft.h op.h fill_bot.c map.c
        champion.c instruct.c sti_ldi.c op.c check_op_h.c ./ncurses/make_scene.c
		./ncurses/ncurses_init_colors.c ./ncurses/ncurses_stats.c
		./ncurses/proc_key.c add_color.c)
add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)