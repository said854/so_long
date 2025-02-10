/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:31:51 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/10 18:36:39 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void handle_error(const char *message)
{
    perror(message);
    exit(1);
}



int check_filename(const char *filename)
{
    int len = ft_strlen(filename);
    
    if (len < 4)
        return 0;
    if (filename[0] == '.')
    {
        return 0;
    }
    if (filename[len - 4] == '.' && filename[len - 3] == 'b' && filename[len - 2] == 'e' && filename[len - 1] == 'r')
    {
        return 1;
    }

    return 0;
}

char **parse_map(const char *filename, int *num_lines)
{
	int fd, i;
	char **map;
	char *line;
    
	i = 0;
	if (!check_filename(filename))
		handle_error("Error: Invalid map name");
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
		map[i++] = line;
	map[i] = NULL;
	close(fd);
	return (map);
}