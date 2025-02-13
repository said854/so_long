/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:30:01 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/13 15:55:14 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_rectangle(t_mlx *mlx, int width, int height)
{
	int	i;
	int	j;
	int	x;
	int	y;

	if (!mlx || !mlx->mlx_win)
		return ;
	i = 0;
	x = 10;
	y = 10;
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

void	*get_tile_image(t_img *img, char tile)
{
	if (tile == '0' && img->template)
		return (img->template);
	if (tile == '1' && img->wall)
		return (img->wall);
	if (tile == 'C' && img->collection)
		return (img->collection);
	if (tile == 'E' && img->door)
		return (img->door);
	if (tile == 'N' && img->enemy)
		return (img->enemy);
	if (tile == 'P' && img->player_frames[img->current_frame])
		return (img->player_frames[img->current_frame]);
	return (NULL);
}

void	put_image_to_window(t_mlx *mlx, t_img *img, int x, int y)
{
	char	tile;
	void	*image;

	tile = mlx->ptr_map[y][x];
	image = get_tile_image(img, tile);
	if (image)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, image, x * 80, y * 80);
}

void	render_map(t_mlx *mlx, t_img *img)
{
	char	*move_count;
	int		x;
	int		y;

	if (!mlx || !img || !mlx->ptr_map)
		return ;
	move_count = ft_itoa(mlx->moves);
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
	draw_rectangle(mlx, 150, 40);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 40, 30, 0xFFFFFF, " MOVES : ");
	mlx_string_put(mlx->mlx, mlx->mlx_win, 100, 30, 0xFFFFFF, move_count);
	free(move_count);
}
