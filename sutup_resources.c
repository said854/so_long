/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutup_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:30:34 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/02 22:45:29 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void validate_collection(char **ptr_map, int lines, t_map *map)
{
    int x, y;
    map->total_collectibles = 0;
    map->collected_items = 0;
    y = -1;
    while (++y < lines)
    {
        x = -1;
        while (ptr_map[y][++x])
            if (ptr_map[y][x] == 'C')
                map->total_collectibles++;
    }
}

void find_player_position(t_map *map, char **ptr_map, int lines)
{
    int x, y;
    y = -1;
    while (++y < lines)
    {
        x = -1;
        while (ptr_map[y][++x])
            if (ptr_map[y][x] == 'P')
            {
                map->x_player = x;
                map->y_player = y;
                return;
            }
    }
}

// void put_image(t_mlx *mlx, int x, int y, char c)
// {
//     if (c == '0')
//         mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.template, x * 80, y * 80);
//     else if (c == '1')
//         mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.wall, x * 80, y * 80);
//     else if (c == 'C')
//         mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.collection, x * 80, y * 80);
//     else if (c == 'E')
//         mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.door, x * 80, y * 80);
//     else if (c == 'P')
//         mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.player, mlx->map->x_player * 80, mlx->map->y_player * 80);
// }


int setup_window(t_mlx *mlx, t_map *map_data)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return (perror("MLX initialization failed"), 1);
    mlx->mlx_win = mlx_new_window(mlx->mlx, map_data->columes * 80,
        map_data->rowes * 80, "so_long");
    if (!mlx->mlx_win)
        return (perror("Failed to create the window"), 1);
    return (0);
}

int load_imgs(t_mlx *mlx)
{
    mlx->img.wall = mlx_xpm_file_to_image(mlx->mlx, "resources/wall.xpm",
        &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.template = mlx_xpm_file_to_image(mlx->mlx, "resources/template.xpm",
        &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player = mlx_xpm_file_to_image(mlx->mlx, "resources/player.xpm",
        &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.collection = mlx_xpm_file_to_image(mlx->mlx, "resources/collection.xpm",
        &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.door = mlx_xpm_file_to_image(mlx->mlx, "resources/door.xpm",
        &mlx->img.img_width, &mlx->img.img_height);
    
    if (!mlx->img.wall || !mlx->img.template || !mlx->img.player 
        || !mlx->img.collection || !mlx->img.door)
        return (perror("Error: Failed to load textures"), free_images(mlx), 1);
    
    return (0);
}
