/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:24:27 by sjoukni           #+#    #+#             */
/*   Updated: 2025/02/02 22:32:06 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int ac, char **av)
{
    t_map map_data;
    t_mlx mlx;

    if (ac < 2)
        return (perror("Error: No file provided"), 1);
    initialize(&mlx, &map_data, av[1]);
    if (setup_window(&mlx, &map_data))
        return (1);
    if (load_imgs(&mlx))
        return (1);
    mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
    mlx_hook(mlx.mlx_win, 17, 0, close_window, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
}
