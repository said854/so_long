/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:26 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/13 16:17:54 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	flood_fill(t_mlx *mlx, int x, int y)
{
	t_map	*map;

	map = mlx->map;
	if (x < 0 || y < 0 || x >= map->rowes || y >= map->columes
		|| mlx->ptr_map[x][y] == '1' || mlx->ptr_map[x][y] == 'V')
		return ;
	if (mlx->ptr_map[x][y] == 'C')
		map->collected_items++;
	if (mlx->ptr_map[x][y] == 'E')
		map->door = 1;
	mlx->ptr_map[x][y] = 'V';
	flood_fill(mlx, x + 1, y);
	flood_fill(mlx, x - 1, y);
	flood_fill(mlx, x, y + 1);
	flood_fill(mlx, x, y - 1);
}

static int	allocate_map(t_mlx *mlx, char **str, int lines)
{
	int	i;

	mlx->ptr_map = malloc(sizeof(char *) * (lines + 1));
	if (!mlx->ptr_map)
		return (0);
	i = 0;
	while (str[i])
	{
		mlx->ptr_map[i] = ft_strdup(str[i]);
		if (!mlx->ptr_map[i])
		{
			free_map(mlx->ptr_map, i);
			return (0);
		}
		i++;
	}
	mlx->ptr_map[i] = NULL;
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
	free_map(mlx.ptr_map, lines);
	if (map->collected_items == map->total_collectibles && map->door)
		return (1);
	ft_putstr_fd("Error\n Some collectibles or exit are unreachable\n", 2);
	return (0);
}
