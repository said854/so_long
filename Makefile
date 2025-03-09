NAME = so_long
B_NAME = so_long_bonus
CC = cc
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror 
MLX = -lmlx -lX11 -lXext -lm
HEADER = so_long.h so_long_bonus.h

SRC_FILES = so_long.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	check_rectangular.c valid_path.c check_map.c check_walls.c \
	parse_map.c free_resources.c setup_game.c sutup_resources.c \
	render_map.c validate_map.c

B_SRC_FILES = so_long_bonus.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	check_rectangular_bonus.c \
	valid_path_bonus.c \
	check_map_bonus.c \
	check_walls_bonus.c \
	parse_map_bonus.c \
	free_resources_bonus.c \
	setup_game_bonus.c \
	sutup_resources_bonus.c \
	render_map_bonus.c \
	validate_map_bonus.c \
	animation_bonus.c

OBJ_FILES = $(SRC_FILES:.c=.o)
B_OBJ_FILES = $(B_SRC_FILES:.c=.o)

all: $(NAME)

bonus: $(B_NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(MLX) $(LIBFT) -o $(NAME)

$(B_NAME): $(B_OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(B_OBJ_FILES) $(MLX) $(LIBFT) -o $(B_NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_FILES) $(B_OBJ_FILES)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(B_NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

