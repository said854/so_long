/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:10:09 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 15:28:26 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	initialize_game(int ac, char **av, t_mlx *mlx, t_map *map_data)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\nInvalid args", 2), 1);
	mlx->moves = 0;
	mlx->map = map_data;
	mlx->ptr_map = parse_map(av[1], &mlx->lines);
	if (!mlx->ptr_map)
		return (ft_putstr_fd("Error\nFailed to parse map", 2), 1);
	validate_map(mlx->ptr_map, mlx->lines, map_data);
	validate_collection(mlx->ptr_map, mlx->lines, map_data);
	find_player_position(map_data, mlx->ptr_map, mlx->lines);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		free_map(mlx->ptr_map, mlx->lines);
		return (ft_putstr_fd("Error\nMLX initialization failed", 2), 1);
	}
	mlx->mlx_win = mlx_new_window(mlx->mlx, map_data->columes * 80,
			map_data->rowes * 80, "so_long");
	if (!mlx->mlx_win)
	{
		free_map(mlx->ptr_map, mlx->lines);
		free(mlx->mlx);
		return (ft_putstr_fd("Error\nFailed to create window", 2), 1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map_data;
	t_mlx	mlx;
	int		i;

	i = 0;
	if (initialize_game(ac, av, &mlx, &map_data))
		return (1);
	load_collection_animation(&mlx);
	load_images(&mlx);
	while (i < 10)
	{
		if (!(mlx.img.collection_frames[i]))
			return (ft_putstr_fd("Error\nFailed textures", 2),
				close_window(&mlx), 1);
		i++;
	}
	if (!mlx.img.wall || !mlx.img.template || !mlx.img.door || !mlx.img.enemy
		|| !mlx.img.player)
		return (ft_putstr_fd("Error\nFailed textures", 2), close_window(&mlx),
			1);
	mlx_loop_hook(mlx.mlx, update_animation, &mlx);
	mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
