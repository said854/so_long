#include "so_long.h"

int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    free_map(mlx->ptr_map, mlx->lines);
    mlx_destroy_window(mlx->mlx, mlx->mlx_win);
    mlx_destroy_display(mlx->mlx);
    free(mlx->mlx);
    exit(0);
}

void validate_collection(char **ptr_map, int lines, t_map *map)
{
    int x, y;

    map->total_collectibles = 0;
    map->collected_items = 0;

    y = 0;
    while (y < lines)
    {
        x = 0;
        while (ptr_map[y][x])
        {
            if (ptr_map[y][x] == 'C')
                map->total_collectibles++;
            x++;
        }
        y++;
    }
}


void find_player_position(t_map *map, char **ptr_map, int lines)
{
    int x, y;
    y = 0;
    while (y < lines)
    {
        x = 0;
        while (ptr_map[y][x])
        {
            if (ptr_map[y][x] == 'P')
            {
                map->x_player = x;
                map->y_player = y;
                return;
            }
            x++;
        }
        y++;
    }
}


void render_map(t_mlx *mlx, t_img *img)
{
    int x, y;

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
            else if(mlx->ptr_map[y][x] == 'P')
            {
                mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img->player, mlx->map->x_player * 80, mlx->map->y_player * 80);

            }
            x++;
        }
        y++;
    }
}

int key_hook(int keycode, t_mlx *param)
{
    int new_x = param->map->x_player;
    int new_y = param->map->y_player;

    if (keycode == 65307) // Escape key
        close_window(param);
    else if (keycode == 65363 && param->ptr_map[new_y][new_x + 1] != '1') // Right
        new_x++;
    else if (keycode == 65361 && param->ptr_map[new_y][new_x - 1] != '1') // Left
        new_x--;
    else if (keycode == 65364 && param->ptr_map[new_y + 1][new_x] != '1') // Down
        new_y++;
    else if (keycode == 65362 && param->ptr_map[new_y - 1][new_x] != '1') // Up
        new_y--;
    if (param->ptr_map[new_y][new_x] == 'E')
    {
        if (param->map->collected_items == param->map->total_collectibles)
        {
            printf("Congratulations! You've collected all items and reached the exit.\n");
            close_window(param);
        }
        else
        {
            return (0);
        }
    }
    if (param->ptr_map[new_y][new_x] != '1')
    {
        if (param->ptr_map[new_y][new_x] == 'C')
        {
            param->map->collected_items++;
        }
        param->ptr_map[param->map->y_player][param->map->x_player] = '0';
        param->map->x_player = new_x;
        param->map->y_player = new_y;
        param->ptr_map[new_y][new_x] = 'P';
    }

    // Redraw the game
    mlx_clear_window(param->mlx, param->mlx_win);
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
    mlx.moves = 0;
    mlx.map = &map_data;
    mlx.ptr_map = parse_map(av[1], &mlx.lines);
    validate_map(mlx.ptr_map, mlx.lines, &map_data);
    validate_collection(mlx.ptr_map, mlx.lines, &map_data);
    find_player_position(&map_data, mlx.ptr_map, mlx.lines);

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

    mlx.img.wall = mlx_xpm_file_to_image(mlx.mlx, "wall.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.template = mlx_xpm_file_to_image(mlx.mlx, "template.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.player = mlx_xpm_file_to_image(mlx.mlx, "player.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.collection = mlx_xpm_file_to_image(mlx.mlx, "collection.xpm", &mlx.img.img_width, &mlx.img.img_height);
    mlx.img.door = mlx_xpm_file_to_image(mlx.mlx, "door.xpm", &mlx.img.img_width, &mlx.img.img_height);

    if (!mlx.img.wall || !mlx.img.template || !mlx.img.player || !mlx.img.collection || !mlx.img.door)
    {
        perror("Error: Failed to load textures");
        exit(1);
    }

    mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
    mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
    mlx_loop(mlx.mlx);

    return (0);
}
