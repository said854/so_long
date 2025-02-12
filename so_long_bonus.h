/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:09:53 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/12 18:39:56 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	int		x_player;
	int		y_player;
	int		columes;
	int		player;
	int		rowes;
	int		door;
	int		enemy;
	int		total_collectibles;
	int		collected_items;
}			t_map;

typedef struct s_img
{
	void	*wall;
	void	*template;
	void	*player;
	void	*collection;
	void	*door;
	void	*enemy;
	void	*player_frames[10];
	int		current_frame;
	int		img_width;
	int		img_height;
	int		frame_delay;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	char	**ptr_map;
	int		lines;
	t_img	img;
	int		moves;
	t_map	*map;
}			t_mlx;

/* LIBRARYS */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char		*get_next_line(int fd);
void		free_map(char **map, int lines);
int			check_rectangular(char **str);
int			valid_path(char **str, t_map *map, int lines);
int			check_map(t_map *map, char **str);
int			count_lines(int fd);
char		**parse_map(const char *filename, int *num_lines);
void		validate_map(char **map, int num_lines, t_map *map_data);
int			check_walls(char *str);
int			check_first_walls(char *str);
void		free_images(t_mlx *mlx);
int			close_window(void *param);
void		handle_move(t_mlx *mlx, int new_x, int new_y);
int			key_hook(int keycode, t_mlx *mlx);
void		render_map(t_mlx *mlx, t_img *img);
void		validate_collection(char **ptr_map, int lines, t_map *map);
void		find_player_position(t_map *map, char **ptr_map, int lines);
int			setup_window(t_mlx *mlx, t_map *map_data);
void		load_images(t_mlx *mlx);
void		handle_error(char *message);
void		load_player_animation(t_mlx *mlx);
int			update_animation(t_mlx *mlx);

#endif