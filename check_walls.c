/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:28:29 by sjoukni           #+#    #+#             */
/*   Updated: 2025/01/27 10:28:42 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_walls(char *str) 
{
    int i = 0;
    while (str[i]) 
    {
        if (str[i] == '\n')
            break;
        if (str[i] != '1') 
            return 0;
        i++;
    }
    return 1;
}

int check_first_walls(char *str)
{
    int len = ft_strlen(str);
    if ((str[0] != '1' || str[len - 2] != '1') && str[0] != '\n') 
    {
        return 0;
    }
    return 1;
}
