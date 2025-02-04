/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:21:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/03 19:17:08 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int check_map_element(t_map *map, char **str) 
{
    int i, j = 0;
    while (str[j]) 
    {
        i = 0;
        while (str[j][i]) 
        {
            // if (str[j][i] == 'N')
            //     map->enemy++;
            if (str[j][i] == 'C')
                map->total_collectibles++;
            else if (str[j][i] == 'E')
                map->door++;
            else if (str[j][i] == 'P')
            {
                map->player++;
                map->x_player = j;
                map->y_player = i;
            }
            else if (str[j][i] != '0' && str[j][i] != '1' && str[j][i] != '\n' && str[j][i] != 'N')
                return 0;
            i++;
        }
        j++;
    }
    return 1;
}
int count_coulume(char **str)
{
    int j;
    j = 0;
    while (str[j])
    {
        j++;
    }
    return (j);
}


int check_map(t_map *map, char **str) 
{
    map->total_collectibles = 0;
    map->collected_items = 0;
    map->door = 0;
    map->player = 0;
    map->x_player = 0;
    map->y_player = 0;
    // map->enemy = 0;
    map->columes = ft_strlen(str[0]) - 1;
    map->rowes = count_coulume(str);
    if (check_map_element(map, str)) 
    {
        if (map->total_collectibles < 1) 
        {
            printf("Error: No collectibles (C) in the map\n");
            return 0;
        }
        if (map->door != 1) 
        {
            printf("Error: There must be exactly 1 exit (E) in the map\n");
            return 0;
        }
        if (map->player != 1) 
        {
            printf("Error: There must be exactly 1 starting position (P) in the map\n");
            return 0;
        }
        if (valid_path(str, map, map->columes) != 1) 
        {
            printf("Error: no valid path\n");
            return 0;
        }
        return 1;
    }
    printf("Error: Invalid characters in the map\n");
    return 0;
}
