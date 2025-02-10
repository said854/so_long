/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:35:41 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 18:36:11 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void validate_map_structure(char **map, int num_lines)
{
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
}

void validate_map_content(char **map, int num_lines, t_map *map_data)
{
	int i = 0;
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

void validate_map(char **map, int num_lines, t_map *map_data)
{
	validate_map_structure(map, num_lines);
	validate_map_content(map, num_lines, map_data);
}