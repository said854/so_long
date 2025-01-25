/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:09:53 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/25 16:34:51 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map
{
	int player ;
    int door;
    int collection;
}		t_map;

/* LIBRARYS */

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stddef.h>

# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif




char	*get_next_line(int fd);



#endif