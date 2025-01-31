#include "so_long.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    free_map(mlx->ptr_map, mlx->lines);
    mlx_destroy_window(mlx->mlx, mlx->mlx_win);
    mlx_destroy_display(mlx->mlx);
    free(mlx->mlx);
    exit(0);
}

int key_hook(int keycode, t_mlx *param)
{
    printf("key = %d\n", keycode);
    printf("x = %d, y = %d\n", param->map->x_player, param->map->y_player);

    if (keycode == 65307) // Escape key
        close_window(param);
    else if (keycode == 65363 && param->ptr_map[param->map->y_player][param->map->x_player + 1] != '1')
        param->map->x_player += 1;
    else if (keycode == 65361 && param->ptr_map[param->map->y_player][param->map->x_player - 1] != '1')
        param->map->x_player -= 1;
    else if (keycode == 65364 && param->ptr_map[param->map->y_player + 1][param->map->x_player] != '1')
        param->map->y_player += 1;
    else if (keycode == 65362 && param->ptr_map[param->map->y_player - 1][param->map->x_player] != '1')
        param->map->y_player -= 1;
    return (0);
}

void render_map(t_mlx *mlx, t_img *img)
{
    int x = 0;
    int y = 0;


    while (y < mlx->lines)
    {
        x = 0;
        while (mlx->ptr_map[y][x])
        {
            if (mlx->ptr_map[y][x] == '1') 
            {
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->img_win, x * 80, y * 80);
            }
            if (mlx->ptr_map[y][x] == '0' || mlx->ptr_map[y][x] == 'P') 
            {
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->img_win2, x * 80, y * 80);
            }
            if (mlx->ptr_map[y][x] == 'C') 
            {
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->img_win4, x * 80, y * 80);
            }
            if (mlx->ptr_map[y][x] == 'E') 
            {
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->img_win5, x * 80, y * 80);
            }
            mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->img_win3,  mlx->map->x_player * 80, mlx->map->y_player * 80);
            x++;
        }
        y++;
    }
}


int ft(t_mlx *param)
{
    render_map(param, &param->img); 
    return (0);
}

int main(int ac, char **av)
{
    t_map map_data;
    t_mlx mlx;

    if (ac < 2)
    {
        perror("Error: No file provided");
        return (1);
    }

    mlx.map = &map_data;
    mlx.ptr_map = parse_map(av[1], &mlx.lines);
    validate_map(mlx.ptr_map, mlx.lines, &map_data);

    mlx.mlx = mlx_init();
    if (!mlx.mlx)
    {
        perror("MLX initialization failed");
        exit(1);
    }

    mlx.mlx_win = mlx_new_window(mlx.mlx, map_data.columes * 80, map_data.rowes * 80, "so_long");
    if (!mlx.mlx_win)
    {
        perror("Failed to create the window");
        exit(1);
    }

    mlx.img.img_win = mlx_xpm_file_to_image(mlx.mlx, "wall.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.img_win2 = mlx_xpm_file_to_image(mlx.mlx, "template1.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.img_win3 = mlx_xpm_file_to_image(mlx.mlx, "player1.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.img_win4 = mlx_xpm_file_to_image(mlx.mlx, "collection.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.img_win5 = mlx_xpm_file_to_image(mlx.mlx, "door.xpm", &mlx.img.img_width, &mlx.img.img_height);
    if (!mlx.img.img_win || !mlx.img.img_win2 || !mlx.img.img_win3)
    {
        perror("Error: Failed to load textures");
        exit(1);
    }

    mlx_loop_hook(mlx.mlx, ft, &mlx);
    mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
    mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
    mlx_loop(mlx.mlx);

    return (0);
}