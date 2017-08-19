cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c corewar.h ./libft/libft.h op.h)
add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar ${CMAKE_SOURCE_DIR}/libft/libft.a)