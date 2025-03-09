/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:21:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 16:30:36 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	validate_elements(t_map *map, char **str)
{
	if (map->total_collectibles < 1)
		return (ft_putstr_fd("Error\nNo collectibles (C)\n", 2), 0);
	if (map->door != 1)
		return (ft_putstr_fd("Error\nThere must be exactly 1 exit (E)\n", 2),
			0);
	if (map->player != 1)
		return (ft_putstr_fd("Error\nThere is no player\n", 2),
			0);
	if (valid_path(str, map, map->rowes) != 1)
		return (ft_putstr_fd("Error\nno valid path\n", 2), 0);
	return (1);
}

static void	update_player_position(t_map *map, int j, int i)
{
	map->player++;
	map->x_player = j;
	map->y_player = i;
}

static int	check_map_element(t_map *map, char **str)
{
	int		i;
	int		j;

	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] == 'C')
				map->total_collectibles++;
			else if (str[j][i] == 'E')
				map->door++;
			else if (str[j][i] == 'P')
				update_player_position(map, j, i);
			else if (str[j][i] == '\n' && i == 0)
				return (0);
			else if (str[j][i] != '0' && str[j][i] != '1' &&
					str[j][i] != 'N' && str[j][i] != '\n')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	count_coulume(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		j++;
	}
	return (j);
}

int	check_map(t_map *map, char **str)
{
	map->total_collectibles = 0;
	map->collected_items = 0;
	map->door = 0;
	map->player = 0;
	map->x_player = 0;
	map->y_player = 0;
	map->columes = ft_strlen(str[0]) - 1;
	map->rowes = count_coulume(str);
	if (check_map_element(map, str))
		return (validate_elements(map, str));
	return (0);
}
