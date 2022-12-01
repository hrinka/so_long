/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:47:49 by takira            #+#    #+#             */
/*   Updated: 2022/12/01 12:47:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static void	destroy_img_arr(t_mlx_vars *mlx, void **arr, int size)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size)
	{
		if (arr[i])
			mlx_destroy_image(mlx->mlx, arr[i]);
		i++;
	}
}

void	destroy_img_ptr_b(t_mlx_vars *mlx)
{
	if (!mlx || !mlx->img)
		return ;
	destroy_img_arr(mlx, mlx->img->players, CNT_PLAYER_FLM * 2);
	destroy_img_arr(mlx, mlx->img->enemies, CNT_ENEMY_FLM * 2);
	destroy_img_arr(mlx, mlx->img->items, CNT_ITEM);
	destroy_img_arr(mlx, mlx->img->empties, CNT_EMPTY);
	if (mlx->img->wall)
		mlx_destroy_image(mlx->mlx, mlx->img->wall);
	if (mlx->img->goal)
		mlx_destroy_image(mlx->mlx, mlx->img->goal);
}
