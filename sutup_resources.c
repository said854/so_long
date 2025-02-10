/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutup_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:30:34 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 18:45:04 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_lines(int fd) 
{
    int line_count = 0;
    char *line;

    while ((line = get_next_line(fd)) != NULL) 
    {
		line_count++;
        free(line); 
    }
    return line_count;
}

void	validate_collection(char **ptr_map, int lines, t_map *map)
{
	int	x;
	int	y;

	map->total_collectibles = 0;
	map->collected_items = 0;
	y = -1;
	while (++y < lines)
	{
		x = -1;
		while (ptr_map[y][++x])
			if (ptr_map[y][x] == 'C')
				map->total_collectibles++;
	}
}

void	find_player_position(t_map *map, char **ptr_map, int lines)
{
	int	x;
	int	y;

	y = -1;
	while (++y < lines)
	{
		x = -1;
		while (ptr_map[y][++x])
			if (ptr_map[y][x] == 'P')
			{
				map->x_player = x;
				map->y_player = y;
				return ;
			}
	}
}

int	setup_window(t_mlx *mlx, t_map *map_data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (perror("MLX initialization failed"), 1);
	mlx->mlx_win = mlx_new_window(mlx->mlx, map_data->columes * 80,
			map_data->rowes * 80, "so_long");
	if (!mlx->mlx_win)
		return (perror("Failed to create the window"), 1);
	return (0);
}


void load_images(t_mlx *mlx)
{
    mlx->img.wall = mlx_xpm_file_to_image(mlx->mlx, "maps/wall.xpm",
            &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.template = mlx_xpm_file_to_image(mlx->mlx, "maps/template.xpm",
            &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.collection = mlx_xpm_file_to_image(mlx->mlx, "maps/collection.xpm",
            &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.door = mlx_xpm_file_to_image(mlx->mlx, "maps/door.xpm",
            &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.enemy = mlx_xpm_file_to_image(mlx->mlx, "maps/enemy.xpm",
            &mlx->img.img_width, &mlx->img.img_height);
}
