cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall") #add -Werror
include_directories(Libft includes srcs srcs/parsing srcs/utils)

set(PARSE_EXE srcs/parsing/config_parsing.c srcs/parsing/resolution_handler.c srcs/parsing/texture_handler.c srcs/parsing/color_handler.c srcs/parsing/config_handler.c srcs/parsing/map_handler.c)
set(UTILS_EXE srcs/utils/string_array_utils.c srcs/utils/color_utils.c)
set(INCLUDES includes/cub3d.h includes/parse.h includes/string_array_utils.h includes/color_utils.h includes/game_engine.h includes/sort_utils.h includes/screenshot.h)
set(GAME_EXE srcs/game/game_init.c srcs/game/keys_handler.c srcs/game/game_render.c srcs/utils/game_utils.c srcs/game/ray/ray_init.c srcs/game/player/player_init.c srcs/game/ray/raycasting.c srcs/game/player/player_move.c srcs/game/texture/textures_init.c srcs/game/texture/textures_handler.c srcs/game/sprites/sprites_init.c srcs/game/sprites/sprites_handler.c srcs/utils/sort_utils.c srcs/screenshot/bitmap_init.c srcs/screenshot/bitmap_handler.c)


add_subdirectory(Libft)

add_executable(Cub3d_project ${INCLUDES} ${PARSE_EXE} ${UTILS_EXE} ${GAME_EXE} main.c)

target_link_libraries(Cub3d_project Libft)
target_link_libraries(Cub3d_project ~/CLionProjects/cub3d/libmlx.a)
target_link_libraries(Cub3d_project "-framework OpenGL")
target_link_libraries(Cub3d_project "-framework AppKit")