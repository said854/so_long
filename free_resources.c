/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:23:51 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/02 22:24:18 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_images(t_mlx *mlx)
{
    for (int i = 0; i < 4; i++)
    {
        if (mlx->img.player_frames[i])
            mlx_destroy_image(mlx->mlx, mlx->img.player_frames[i]);
    }
    if (mlx->img.wall)
        mlx_destroy_image(mlx->mlx, mlx->img.wall);
    if (mlx->img.template)
        mlx_destroy_image(mlx->mlx, mlx->img.template);
    if (mlx->img.collection)
        mlx_destroy_image(mlx->mlx, mlx->img.collection);
    if (mlx->img.door)
        mlx_destroy_image(mlx->mlx, mlx->img.door);
}

// void free_all(t_mlx *mlx)
// {
//     free_images(mlx);
//     free_map(mlx->ptr_map, mlx->lines);
//     mlx_clear_window(mlx->mlx, mlx->mlx_win);
//     if (mlx->mlx_win)
//         mlx_destroy_window(mlx->mlx, mlx->mlx_win);
//     if (mlx->mlx)
//     {
//         mlx_destroy_display(mlx->mlx);
//         free(mlx->mlx);
//     }
// }

// int close_window(void *param)
// {
//     free_all((t_mlx *)param);
//     exit(0);
// }
int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    free_images(mlx);
    free_map(mlx->ptr_map, mlx->lines);
    mlx_clear_window(mlx->mlx, mlx->mlx_win);
    if (mlx->mlx_win)
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);
    if (mlx->mlx)
    {
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
    }
    exit(0);
}
