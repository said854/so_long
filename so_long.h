/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:09:53 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/31 21:47:50 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map
{
	int player ;
    int door;
    int collection;
    int x_player;
    int y_player;
    int columes;
    int rowes;
}		t_map;

typedef struct s_img
{
    void *img_win;
    void *img_win2;
    void *img_win3;
    void *img_win4;
    void *img_win5;
    int img_width;
    int img_height;
}              t_img;

typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    char **ptr_map;
    int lines;
    t_img img;
    t_map *map;
}              t_mlx;


/* LIBRARYS */

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <mlx.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif




char	*get_next_line(int fd);
void free_map(char **map, int lines);
int check_rectangular(char **str);
int valid_path(char **str, t_map *map, int lines);
int check_map(t_map *map, char **str);
int count_lines(int fd);
char **parse_map(const char *filename, int *num_lines);
void validate_map(char **map, int num_lines, t_map *map_data);
int check_walls(char *str); 
int check_first_walls(char *str);



#endif