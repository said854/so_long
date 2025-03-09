/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:31:51 by sjoukni           #+#    #+#             */
/*   Updated: 2025/03/01 15:23:57 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	handle_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

int	check_filename(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || filename[0] == '.')
		return (0);
	if ((filename[len - 4] == '.') && (filename[len - 3] == 'b')
		&& (filename[len - 2] == 'e') && (filename[len - 1] == 'r'))
		return (1);
	return (0);
}

char	**allocate_map(int num_lines)
{
	char	**map;

	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
		handle_error("Error: Memory allocation failed");
	return (map);
}

char	**read_map_lines(int fd, int num_lines)
{
	char	**map;
	char	*line;
	int		i;

	map = allocate_map(num_lines);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

char	**parse_map(const char *filename, int *num_lines)
{
	int		fd;
	char	**map;

	if (!check_filename(filename))
		handle_error("Error\nInvalid map name");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Error\nFailed to open file");
	*num_lines = count_lines(fd);
	if (*num_lines == 0)
		handle_error("Error\nFile is empty or invalid");
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Error\nFailed to reopen file");
	map = read_map_lines(fd, *num_lines);
	close(fd);
	return (map);
}
