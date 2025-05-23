/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:30:01 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/17 16:07:43 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (tile == 'P' && img->player)
		return (img->player);
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
	int		x;
	int		y;

	if (!mlx || !img || !mlx->ptr_map)
		return ;
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
}
