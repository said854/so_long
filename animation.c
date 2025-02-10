/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:42:11 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 18:46:30 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_player_animation_frames(t_mlx *mlx, int i, char *filenames[])
{
    while (i < 10)
    {
        mlx->img.player_frames[i] = mlx_xpm_file_to_image(mlx->mlx,
                filenames[i], &mlx->img.img_width, &mlx->img.img_height);
        i++;
    }
}

void load_player_animation(t_mlx *mlx)
{
    char *filenames[10] = {
        "textures/player1.xpm", "textures/player2.xpm", "textures/player3.xpm",
        "textures/player4.xpm", "textures/player5.xpm", "textures/player6.xpm",
        "textures/player7.xpm", "textures/player8.xpm", "textures/player9.xpm",
        "textures/player10.xpm"
    };
    load_player_animation_frames(mlx, 0, filenames);
    mlx->img.current_frame = 0;
}

int update_animation(t_mlx *mlx)
{
    static int frame_count = 0;
    
    if (frame_count % 10 == 0)
    {
       mlx->img.current_frame++;
       if (mlx->img.current_frame > 9)
       {
            frame_count = 0;
            mlx->img.current_frame = 0;
       }
    }
    frame_count++;
    return (0);
}
