/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:19:26 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/27 10:20:32 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

static void flood_fill(char **map, int x, int y, int rows, int cols, int *collectibles, int *exit_found) 
{
    if (x < 0 || y < 0 || x >= rows || y >= cols || map[x][y] == '1' || map[x][y] == 'V')
        return;

    if (map[x][y] == 'C')
        (*collectibles)++;
    if (map[x][y] == 'E')
        *exit_found = 1;
    map[x][y] = 'V'; 

    flood_fill(map, x + 1, y, rows, cols, collectibles, exit_found); // Down
    flood_fill(map, x - 1, y, rows, cols, collectibles, exit_found); // Up
    flood_fill(map, x, y + 1, rows, cols, collectibles, exit_found); // Right
    flood_fill(map, x, y - 1, rows, cols, collectibles, exit_found); // Left
}

int valid_path(char **str, t_map *map, int lines)
{
    char **map_copy;
    int i = 0;
    int collectibles = 0, exit_found = 0;

    map_copy = malloc(sizeof(char *) * (lines + 1)); 
    while (str[i])
    {
        map_copy[i] = ft_strdup(str[i]); 
        i++;
    }
    map_copy[i] = NULL;

    flood_fill(map_copy, map->x_player, map->y_player, lines, ft_strlen(map_copy[0]), &collectibles, &exit_found);

    if (collectibles == map->collection && exit_found)
    {
        printf("All collectibles and exit are reachable\n");
        free_map(map_copy, lines);
        return 1;
    }
    else
    {
        printf("Some collectibles or exit are unreachable\n");
        free_map(map_copy, lines);
        return 0;
    }
}
