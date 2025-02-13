/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:10:09 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/13 16:10:10 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	initialize_game(int ac, char **av, t_mlx *mlx, t_map *map_data)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\n No file provided", 2), 1);
	mlx->moves = 0;
	mlx->map = map_data;
	mlx->ptr_map = parse_map(av[1], &mlx->lines);
	validate_map(mlx->ptr_map, mlx->lines, map_data);
	validate_collection(mlx->ptr_map, mlx->lines, map_data);
	find_player_position(map_data, mlx->ptr_map, mlx->lines);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (ft_putstr_fd("Error\n MLX initialization failed", 2), 1);
	mlx->mlx_win = mlx_new_window(mlx->mlx, map_data->columes * 80,
			map_data->rowes * 80, "so_long");
	if (!mlx->mlx_win)
		return (ft_putstr_fd("Error\n Failed to create the window", 2), 1);
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
	load_player_animation(&mlx);
	load_images(&mlx);
	while (i < 10)
	{
		if (!(mlx.img.player_frames[i]))
			return (ft_putstr_fd("Error\nFailed textures", 2),
				close_window(&mlx), 1);
		i++;
	}
	if (!mlx.img.wall || !mlx.img.template || !mlx.img.collection
		|| !mlx.img.door || !mlx.img.enemy)
		return (ft_putstr_fd("Error\nFailed textures", 2), close_window(&mlx),
			1);
	mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
	mlx_loop_hook(mlx.mlx, update_animation, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
