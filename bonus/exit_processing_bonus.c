/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_processing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:01:58 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:22:22 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

int	err_exit_b(char *msg, t_mlx_vars *mlx)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
		ft_printf(" ** strerror : %s", strerror(errno));
	if (mlx)
		destroy_mlx_and_map_b(mlx);
	exit(EXIT_FAILURE);
}

int	free_map_arr_b(t_map_param *map, int ret_val)
{
	size_t	y;

	y = 0;
	if (map->map_arr)
		while (y < map->size_y)
			free(map->map_arr[y++]);
	free(map->map_arr);
	return (ret_val);
}

void	free_grid_b(int **grid, size_t y)
{
	size_t	i;

	i = 0;
	while (i < y)
		free(grid[i++]);
	free(grid);
}

void	free_alloc_img_arr_b(t_img *img)
{
	free(img->players);
	free(img->enemies);
	free(img->empties);
	free(img->items);
}
