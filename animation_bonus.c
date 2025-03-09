/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:42:11 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 16:57:51 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_collection_animation_frames(t_mlx *mlx, int i, char *filenames[])
{
	while (i < 10)
	{
		mlx->img.collection_frames[i] = mlx_xpm_file_to_image(mlx->mlx,
				filenames[i], &mlx->img.img_width, &mlx->img.img_height);
		i++;
	}
}

void	load_collection_animation(t_mlx *mlx)
{
	char	*filenames[10];

	filenames[0] = "textures/collection.xpm";
	filenames[1] = "textures/collection1.xpm";
	filenames[2] = "textures/collection2.xpm";
	filenames[3] = "textures/collection3.xpm";
	filenames[4] = "textures/collection4.xpm";
	filenames[5] = "textures/collection5.xpm";
	filenames[6] = "textures/collection6.xpm";
	filenames[7] = "textures/collection7.xpm";
	filenames[8] = "textures/collection8.xpm";
	filenames[9] = "textures/collection9.xpm";
	load_collection_animation_frames(mlx, 0, filenames);
	mlx->img.current_frame = 0;
}

int	update_animation(t_mlx *mlx)
{
	static int	frame_count = 0;

	frame_count++;
	render_map(mlx, &mlx->img);
	if (frame_count >= 300)
	{
		frame_count = 0;
		mlx->img.current_frame++;
		if (mlx->img.current_frame > 9)
			mlx->img.current_frame = 0;
	}
	return (0);
}
