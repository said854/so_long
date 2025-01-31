/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:26:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/27 10:27:20 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_lines(int fd) 
{
    int line_count = 0;
    char *line;

    while ((line = get_next_line(fd)) != NULL) 
    {
        line_count++;
        free(line); 
    }
    return line_count;
}