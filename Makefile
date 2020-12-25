CC = gcc

NAME = cub3D

CFLAGS = -Wall -Wextra

MLXFLAGS = -framework OpenGL -framework AppKit

LIBFT = libft

LIBMLX = libmlx.a

LIBS = $(LIBFT)/libft.a $(LIBMLX)

DIR_S = srcs

PARSE_DIR = $(DIR_S)/parsing

GAME_DIR = $(DIR_S)/game

UTILS_DIR = $(DIR_S)/utils

SCREENSHOT_DIR = $(DIR_S)/screenshot

GAME_PLAYER_DIR = $(GAME_DIR)/player

GAME_RAY_DIR = $(GAME_DIR)/ray

GAME_SPRITES_DIR = $(GAME_DIR)/sprites

GAME_TEXTURE_DIR = $(GAME_DIR)/texture

INCLUDES = includes

SRC =	$(GAME_PLAYER_DIR)/player_init.c \
		$(GAME_PLAYER_DIR)/player_move.c \
		$(GAME_RAY_DIR)/ray_init.c \
		$(GAME_RAY_DIR)/raycasting.c \
		$(GAME_SPRITES_DIR)/sprites_init.c \
		$(GAME_SPRITES_DIR)/sprites_handler.c \
		$(GAME_TEXTURE_DIR)/textures_handler.c \
		$(GAME_TEXTURE_DIR)/textures_init.c
		$(GAME_DIR)/game_init.c \
		$(GAME_DIR)/game_render.c \
		$(GAME_DIR)/keys_handler.c \
		$(GAME_DIR)/my_mlx_functions.c \
		$(PARSE_DIR)/color_handler.c \
		$(PARSE_DIR)/config_handler.c \
		$(PARSE_DIR)/config_parsing.c \
		$(PARSE_DIR)/map_handler.c \
		$(PARSE_DIR)/resolution_handler.c \
		$(PARSE_DIR)/texture_handler.c \
		$(SCREENSHOT_DIR)/bitmap_init.c \
		$(SCREENSHOT_DIR)/bitmap_handler.c \
		$(UTILS_DIR)/color_utils.c \
		$(UTILS_DIR)/sort_utils.c \
		$(UTILS_DIR)/string_array_utils.c


OBJS = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) -I$(INCLD) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT)
	@$(CC) $(FLAGS) $(MLXFLAGS) $(LIBS) -I$(INCLUDES) -c $< -o $(<:.c=.o)
	@echo "Compile cub3d done!"

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@echo "Clean .o files done!"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "Clean libftprintf.a done!"

norme:
	norminette ./$(LIBFT)/
	@echo
	norminette ./$(INCLUDES)/
	@echo
	norminette ./$(DIR_S)/

re: fclean all