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
	ft_printf("[Error] %s\n", msg);
	exit(EXIT_FAILURE);
}

int	free_map_arr(t_map_info *info, int ret_val)
{
	size_t	col;

	col = 0;
	if (info->map_arr)
		while (col < info->size_col)
			free(info->map_arr[col++]);
	free(info->map_arr);
	return (ret_val);
}

int	get_map_kinds(void **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	print_step_in_std(t_mlx_vars *mlx)
{
	if (mlx->player_ptr->flg_get_item)
	{
		ft_printf(" Step:%d  Item:%d/%d\n", \
		mlx->player_ptr->cnt_step, \
		mlx->player_ptr->cnt_item, \
		mlx->map_ptr->cnt_item);
		mlx->player_ptr->flg_get_item = false;
	}
	else
		ft_printf(" Step:%d\n", mlx->player_ptr->cnt_step);
}
