/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_maps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:23:51 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 10:07:33 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(char **map, int lines) 
{
    int i = 0;
    while (i < lines && map[i]) 
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_images(t_mlx *mlx)
{
    int i;
    
    i = 0;
    while(i < 10)
    {
        if (mlx->img.player_frames[i])
            mlx_destroy_image(mlx->mlx, mlx->img.player_frames[i]);
        i++;
    }
    if (mlx->img.wall)
        mlx_destroy_image(mlx->mlx, mlx->img.wall);
    if (mlx->img.template)
        mlx_destroy_image(mlx->mlx, mlx->img.template);
    if (mlx->img.collection)
        mlx_destroy_image(mlx->mlx, mlx->img.collection);
    if (mlx->img.door)
        mlx_destroy_image(mlx->mlx, mlx->img.door);
    if (mlx->img.enemy)
        mlx_destroy_image(mlx->mlx, mlx->img.enemy);
}

int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    free_images(mlx);
    free_map(mlx->ptr_map, mlx->lines);
    
    if (mlx->mlx_win)
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);

    if (mlx->mlx)
    {
        mlx_loop_end(mlx->mlx);
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
    }
    
    exit(0);
}
