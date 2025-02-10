/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:30:01 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 18:31:44 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_rectangle(t_mlx *mlx, int x, int y, int width, int height)
{
	int i, j;

	if (!mlx || !mlx->mlx_win)
		return;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(mlx->mlx, mlx->mlx_win, x + j, y + i, 0x000000);
			j++;
		}
		i++;
	}
}

void	put_image_to_window(t_mlx *mlx, t_img *img, int x, int y)
{
	char tile = mlx->ptr_map[y][x];
	if (tile == '0' && img->template)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->template, x * 80, y * 80);
	else if (tile == '1' && img->wall)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->wall, x * 80, y * 80);
	else if (tile == 'C' && img->collection)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->collection, x * 80, y * 80);
	else if (tile == 'E' && img->door)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->door, x * 80, y * 80);
	else if (tile == 'N' && img->enemy)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->enemy, x * 80, y * 80);
	else if (tile == 'P' && img->player_frames[img->current_frame])
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->player_frames[img->current_frame],
						mlx->map->x_player * 80, mlx->map->y_player * 80);
}

void	render_map(t_mlx *mlx, t_img *img)
{
	char *move_count;
	int x, y;

	if (!mlx || !img || !mlx->ptr_map)
		return;
	y = 0;
	while (y < mlx->lines)
	{
		x = 0;
		while (mlx->ptr_map[y][x])
		{
			put_image_to_window(mlx, img, x, y);
			x++;
		}
		y++;
	}
	move_count = ft_itoa(mlx->moves);
	draw_rectangle(mlx, 10, 10, 150, 40);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20, 30, 0xFFFFFF, "Moves: ");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 80, 30, 0xFFFFFF, move_count);
	free(move_count);
}