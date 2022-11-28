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

void	print_step_or_finish_to_stdout(t_mlx_vars *mlx)
{
	if (mlx->player->flg_get_item)
	{
		ft_printf(" Step:%d  Item:%d/%d\n", \
		mlx->player->cnt_step, \
		mlx->player->cnt_item, \
		mlx->map->cnt_item);
		mlx->player->flg_get_item = false;
	}
	else
		ft_printf(" Step:%d\n", mlx->player->cnt_step);
	if (mlx->is_game_end)
	{
		ft_printf("### GAME CLEAR!!! :D ###\n");
		close_window(mlx);
	}
}
