/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:04:19 by takira            #+#    #+#             */
/*   Updated: 2022/11/27 13:04:20 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

int	error_exit(char *msg)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
		ft_printf(" ** strerror : %s", strerror(errno));
	exit(EXIT_FAILURE);
}

void	error_print(char *msg)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
		ft_printf(" ** strerror : %s", strerror(errno));
}

int	free_map_arr(t_map_param *map, int ret_val)
{
	size_t	y;

	y = 0;
	if (map->map_arr)
		while (y < map->size_y)
			free(map->map_arr[y++]);
	free(map->map_arr);
	return (ret_val);
}

void	print_step_to_stdout(t_mlx_vars *mlx)
{
	const int	player_step = (int)mlx->player->cnt_step;
	const int	player_item = (int)mlx->player->cnt_item;
	const int	map_item = (int)mlx->map->cnt_item;

	if (mlx->player->flg_get_item)
	{
		ft_printf(" Step:%d  Item:%d/%d\n", player_step, player_item, map_item);
		mlx->player->flg_get_item = false;
	}
	else
		ft_printf(" Step:%d\n", player_step);
}
