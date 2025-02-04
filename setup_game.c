/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:26:45 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/04 20:41:24 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void handle_move(t_mlx *mlx, int new_x, int new_y)
{
    if (mlx->ptr_map[new_y][new_x] == '1')
        return;

    if (mlx->ptr_map[new_y][new_x] == 'E')
    {
        if (mlx->map->collected_items == mlx->map->total_collectibles)
        {
            printf("Congratulations! You won!\n");
            close_window(mlx);
        }
        return;
    }

    if (new_x != mlx->map->x_player || new_y != mlx->map->y_player)
    {
        if (mlx->ptr_map[new_y][new_x] == 'C') 
            mlx->map->collected_items++;

        mlx->ptr_map[mlx->map->y_player][mlx->map->x_player] = '0';
        mlx->map->x_player = new_x;
        mlx->map->y_player = new_y;
        mlx->ptr_map[new_y][new_x] = 'P';

        mlx->moves++;
        printf("Number of moves = %d\n", mlx->moves);
    }

    render_map(mlx, &mlx->img);
}


int key_hook(int keycode, t_mlx *mlx)
{
    int new_x = mlx->map->x_player;
    int new_y = mlx->map->y_player;
    if (keycode == 65307)
        close_window(mlx);
    else if ((keycode == 65363 || keycode == 100) && mlx->ptr_map[new_y][new_x + 1] != '1')
        new_x++;
    else if ((keycode == 65361 || keycode == 97) && mlx->ptr_map[new_y][new_x - 1] != '1')
        new_x--;
    else if ((keycode == 65364 || keycode == 115) && mlx->ptr_map[new_y + 1][new_x] != '1')
        new_y++;
    else if ((keycode == 65362 || keycode == 119) && mlx->ptr_map[new_y - 1][new_x] != '1')
        new_y--;
    handle_move(mlx, new_x, new_y);
    return (0);
}


void render_map(t_mlx *mlx, t_img *img)
{
    int x, y;
    char *move_count;

    y = 0;
    while (y < mlx->lines)
    {
        x = 0;
        while (mlx->ptr_map[y][x])
        {
            if (mlx->ptr_map[y][x] == '0')
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->template, x * 80, y * 80);
            else if (mlx->ptr_map[y][x] == '1') 
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->wall, x * 80, y * 80);
            else if (mlx->ptr_map[y][x] == 'C') 
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->collection, x * 80, y * 80);
            else if (mlx->ptr_map[y][x] == 'E') 
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->door, x * 80, y * 80);
            else if (mlx->ptr_map[y][x] == 'N') 
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->enemy, x * 80, y * 80);
            else if (mlx->ptr_map[y][x] == 'P')
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->player_frames[img->current_frame], mlx->map->x_player * 80, mlx->map->y_player * 80);
            x++;
        }
        y++;
    }

    move_count = ft_itoa(mlx->moves); // Convert int to string
    mlx_string_put(mlx->mlx, mlx->mlx_win, 20, 20, 0xFFFFFF, "Moves: ");
    mlx_string_put(mlx->mlx, mlx->mlx_win, 80, 20, 0xFFFFFF, move_count);
    
    // free(move_count); // Avoid memory leaks
}


void initialize(t_mlx *mlx, t_map *map_data, char *filename)
{
    mlx->moves = 0;
    mlx->map = map_data;
    mlx->ptr_map = parse_map(filename, &mlx->lines);
    validate_map(mlx->ptr_map, mlx->lines, map_data);
    validate_collection(mlx->ptr_map, mlx->lines, map_data);
    find_player_position(map_data, mlx->ptr_map, mlx->lines);
}


// void render_map(t_mlx *mlx, t_img *img)
// {
//     int x, y;
//     y = 0;
//     while (y < mlx->lines)
//     {
//         x = 0;
//         while (mlx->ptr_map[y][x])
//         {
//             if (mlx->ptr_map[y][x] == '0')
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->template, x * 80, y * 80);
//             else if (mlx->ptr_map[y][x] == '1') 
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->wall, x * 80, y * 80);
//             else if (mlx->ptr_map[y][x] == 'C') 
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->collection, x * 80, y * 80);
//             else if (mlx->ptr_map[y][x] == 'E') 
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->door, x * 80, y * 80);
//             else if (mlx->ptr_map[y][x] == 'N') 
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->enemy, x * 80, y * 80);
//             else if (mlx->ptr_map[y][x] == 'P')
//                 mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->player_frames[img->current_frame], mlx->map->x_player * 80, mlx->map->y_player * 80);
//             x++;
//         }
//         y++;
//     }
// }

// void initialize(t_mlx *mlx, t_map *map_data, char *filename)
// {
//     mlx->moves = 0;
//     mlx->map = map_data;
//     mlx->ptr_map = parse_map(filename, &mlx->lines);
//     validate_map(mlx->ptr_map, mlx->lines, map_data);
//     validate_collection(mlx->ptr_map, mlx->lines, map_data);
//     find_player_position(map_data, mlx->ptr_map, mlx->lines);
// }
