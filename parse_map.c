/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:31:51 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/30 09:32:32 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void handle_error(const char *message)
{
    perror(message);
    exit(1);
}

void validate_map(char **map, int num_lines, t_map *map_data)
{
    int i ;

    i = 0;
    if (!check_rectangular(map))
    {
        free_map(map, num_lines);
        handle_error("Error: The map is not rectangular");
    }
    if (!check_walls(map[0]) || !check_walls(map[num_lines - 1]))
    {
        free_map(map, num_lines);
        handle_error("Error: The map is not surrounded by walls");
    }
    while (map[i])
    {
        if (!check_first_walls(map[i]))
        {
            free_map(map, num_lines);
            handle_error("Error: The map is not enclosed by walls at row");
        }
        i++;
    }
    if (!check_map(map_data, map))
    {
        free_map(map, num_lines);
        handle_error("Error: Invalid map content");
    }
}


char **parse_map(const char *filename, int *num_lines)
{
    int fd;
    char **map;
    char *line;
    int i = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Error: Failed to open file");
    *num_lines = count_lines(fd);
    if (*num_lines == 0)
        handle_error("Error: File is empty or invalid");
    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Error: Failed to reopen file");
    map = malloc(sizeof(char *) * (*num_lines + 1));
    if (!map)
        handle_error("Error: Memory allocation failed");
    while ((line = get_next_line(fd)) != NULL)
    {
        map[i++] = line;
    }
    map[i] = NULL;
    close(fd);
    return (map);
}
