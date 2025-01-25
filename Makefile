NAME = so_long
CC = cc
LIBFT = libft.a
CFLAGS = -Wall -Wextra -Werror
MLX = libmlx.a -lX11 -lXext -lm
SRC_FILES = main.c get_next_line.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) mlx/$(MLX) libft/$(LIBFT) -o $(NAME)

$(LIBFT) :
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_FILES) libft/*.o

fclean: clean
	rm -f $(NAME) libft/$(LIBFT)

re: fclean all

.PHONY: all clean fclean re
