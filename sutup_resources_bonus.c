/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutup_resources_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:52 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 17:02:59 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	count_lines(int fd)
{
	int		line_count;
	char	*line;

	line = get_next_line(fd);
	line_count = 0;
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (line_count);
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
		{
			if (ptr_map[y][x] == 'P')
			{
				map->x_player = x;
				map->y_player = y;
				return ;
			}
		}
	}
}

void	load_images(t_mlx *mlx)
{
	mlx->img.wall = mlx_xpm_file_to_image(mlx->mlx, "textures/wall.xpm",
			&mlx->img.img_width, &mlx->img.img_height);
	mlx->img.template = mlx_xpm_file_to_image(mlx->mlx, "textures/template.xpm",
			&mlx->img.img_width, &mlx->img.img_height);
	mlx->img.player = mlx_xpm_file_to_image(mlx->mlx, "textures/player.xpm",
			&mlx->img.img_width, &mlx->img.img_height);
	mlx->img.door = mlx_xpm_file_to_image(mlx->mlx, "textures/door.xpm",
			&mlx->img.img_width, &mlx->img.img_height);
	mlx->img.enemy = mlx_xpm_file_to_image(mlx->mlx, "textures/enemy.xpm",
			&mlx->img.img_width, &mlx->img.img_height);
}
