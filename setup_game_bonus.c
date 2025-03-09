/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:53:33 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 15:29:33 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	process_player_movement(t_mlx *mlx, int new_x, int new_y)
{
	if (mlx->ptr_map[new_y][new_x] == 'C')
		mlx->map->collected_items++;
	if (mlx->ptr_map[mlx->map->y_player][mlx->map->x_player] != 'E')
		mlx->ptr_map[mlx->map->y_player][mlx->map->x_player] = '0';
	if (mlx->ptr_map[new_y][new_x] != 'E')
		mlx->ptr_map[new_y][new_x] = 'P';
	mlx->map->x_player = new_x;
	mlx->map->y_player = new_y;
	mlx->moves++;
}

void	handle_move(t_mlx *mlx, int new_x, int new_y)
{
	if (!mlx || !mlx->map || !mlx->ptr_map || mlx->ptr_map[new_y][new_x] == '1')
		return ;
	if (mlx->ptr_map[new_y][new_x] == 'N')
	{
		printf("You lose!\n");
		close_window(mlx);
		return ;
	}
	if (mlx->ptr_map[new_y][new_x] == 'E' &&
		mlx->map->collected_items == mlx->map->total_collectibles)
	{
		ft_putstr_fd("Congratulations! You won!\n", 1);
		close_window(mlx);
		return ;
	}
	if (new_x != mlx->map->x_player || new_y != mlx->map->y_player)
		process_player_movement(mlx, new_x, new_y);
	render_map(mlx, &mlx->img);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	int	new_x;
	int	new_y;

	if (!mlx || !mlx->map || !mlx->ptr_map)
		return (0);
	new_x = mlx->map->x_player;
	new_y = mlx->map->y_player;
	if (keycode == 65307)
		close_window(mlx);
	else if ((keycode == 65363 || keycode == 100) && mlx->ptr_map[new_y][new_x
		+ 1] != '1')
		new_x++;
	else if ((keycode == 65361 || keycode == 97) && mlx->ptr_map[new_y][new_x
		- 1] != '1')
		new_x--;
	else if ((keycode == 65364 || keycode == 115) && mlx->ptr_map[new_y
			+ 1][new_x] != '1')
		new_y++;
	else if ((keycode == 65362 || keycode == 119) && mlx->ptr_map[new_y
			- 1][new_x] != '1')
		new_y--;
	handle_move(mlx, new_x, new_y);
	return (0);
}
