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

size_t	ft_strlen_sl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	error_exit(char *msg)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
	{
		ft_printf("errno:");
		strerror(errno);
	}
	exit(EXIT_FAILURE);
}

int	free_map_arr(t_map_info *map, int ret_val)
{
	size_t	col;

	col = 0;
	if (map->map_arr)
		while (col < map->size_col)
			free(map->map_arr[col++]);
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
