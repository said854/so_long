/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rectangular.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:16:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/16 18:46:44 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_slen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

int	check_rectangular(char **str)
{
	int	i;
	int	len;

	len = ft_slen(str[0]);
	i = 1;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i][0] == '\n')
		{
			break ;
		}
		if (ft_slen(str[i]) != len)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
