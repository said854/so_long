/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:26 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 15:22:37 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	flood_fill(t_mlx *mlx, int x, int y)
{
	t_map	*map;

	map = mlx->map;
	if (x < 0 || y < 0 || x >= map->rowes || y >= map->columes
		|| mlx->copy[x][y] == '1' || mlx->copy[x][y] == 'V'
		|| mlx->copy[x][y] == 'N')
		return ;
	if (mlx->copy[x][y] == 'C')
		map->collected_items++;
	if (mlx->copy[x][y] == 'E')
		map->door = 1;
	mlx->copy[x][y] = 'V';
	flood_fill(mlx, x + 1, y);
	flood_fill(mlx, x - 1, y);
	flood_fill(mlx, x, y + 1);
	flood_fill(mlx, x, y - 1);
}

static int	allocate_map(t_mlx *mlx, char **str, int lines)
{
	int	i;

	mlx->copy = malloc(sizeof(char *) * (lines + 1));
	if (!mlx->copy)
		return (0);
	i = 0;
	while (str[i])
	{
		mlx->copy[i] = ft_strdup(str[i]);
		if (!mlx->copy[i])
		{
			free_map(mlx->copy, i);
			return (0);
		}
		i++;
	}
	mlx->copy[i] = NULL;
	return (1);
}

int	valid_path(char **str, t_map *map, int lines)
{
	t_mlx	mlx;

	mlx.map = map;
	mlx.map->collected_items = 0;
	mlx.map->door = 0;
	mlx.lines = lines;
	if (!allocate_map(&mlx, str, lines))
		return (0);
	flood_fill(&mlx, map->x_player, map->y_player);
	free_map(mlx.copy, lines);
	if (map->collected_items == map->total_collectibles && map->door)
		return (1);
	return (0);
}
