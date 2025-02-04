/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:24:27 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/04 20:52:02 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"





void load_player_animation(t_mlx *mlx)
{
    mlx->img.player_frames[0] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (10)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[1] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (11)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[2] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (12)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[3] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (13)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[4] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (14)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[5] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (15)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[6] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (16)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[7] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (17)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[8] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (18)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.player_frames[9] = mlx_xpm_file_to_image(mlx->mlx, "test/New Project (19)-resized.xpm", &mlx->img.img_width, &mlx->img.img_height);
    mlx->img.current_frame = 0;
}

int update_animation(t_mlx *mlx)
{
    static int frame_count = 0;
    
    if (frame_count % 20 == 0)
    {
       mlx->img.current_frame++;
       if (mlx->img.current_frame > 9)
       {
            frame_count = 0;
            mlx->img.current_frame = 0;
       }
    }
    // printf("fram = %d\n", mlx->img.current_frame);
    frame_count++;
    // render_map(mlx, &mlx->img);
    return (0);
}


int main(int ac, char **av)
{
    t_map map_data;
    t_mlx mlx;
    if (ac != 2)
        return (perror("Error: No file provided"), 1);
    mlx.moves = 0;
    mlx.map = &map_data;
    mlx.ptr_map = parse_map(av[1], &mlx.lines);
    validate_map(mlx.ptr_map, mlx.lines, &map_data);
    validate_collection(mlx.ptr_map, mlx.lines, &map_data);
    find_player_position(&map_data, mlx.ptr_map, mlx.lines);
    mlx.mlx = mlx_init();
    if (!mlx.mlx)
        return (perror("MLX initialization failed"), 1);
    mlx.mlx_win = mlx_new_window(mlx.mlx, map_data.columes * 80, map_data.rowes * 80, "so_long");
    if (!mlx.mlx_win)
        return (perror("Failed to create the window"), 1);
    load_player_animation(&mlx);
    mlx.img.wall = mlx_xpm_file_to_image(mlx.mlx, "resources/wall.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.template = mlx_xpm_file_to_image(mlx.mlx, "resources/template.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.collection = mlx_xpm_file_to_image(mlx.mlx, "resources/collection.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.door = mlx_xpm_file_to_image(mlx.mlx, "resources/door.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.enemy = mlx_xpm_file_to_image(mlx.mlx, "resources/enemy.xpm", &mlx.img.img_width, &mlx.img.img_height);
    if (!mlx.img.wall || !mlx.img.template || !mlx.img.collection || !mlx.img.door)
        return (perror("Error: Failed to load textures"), free_images(&mlx), 1);
    mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
    mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
    mlx_loop_hook(mlx.mlx, update_animation, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
}


