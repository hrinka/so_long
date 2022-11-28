/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:00:23 by takira            #+#    #+#             */
/*   Updated: 2022/11/28 17:00:24 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

void	*get_player_img(t_mlx_vars mlx)
{
	if (mlx.player_ptr->is_facing_right)
		return (mlx.img_ptr->player_right);
	return (mlx.img_ptr->player_left);
}

void	*get_empty_img(t_mlx_vars mlx, int row, int col)
{
	if ((row + col) % 2 == 0)
		return (mlx.img_ptr->empty1);
	else if ((row + col) % 7 == 0)
		return (mlx.img_ptr->empty3);
	else if ((row + col) % 3 == 0)
		return (mlx.img_ptr->empty4);
	return (mlx.img_ptr->empty2);
}

void	*get_item_img(t_mlx_vars mlx, int row, int col)
{
	if ((row + col) % 2 == 0)
		return (mlx.img_ptr->item1);
	return (mlx.img_ptr->item2);
}

void	*get_img_ptr(t_mlx_vars *mlx, int row, int col)
{
	if (mlx->map_ptr->map_arr[col][row] == CHR_MAP_WALL)
		return (mlx->img_ptr->wall);
	if (mlx->map_ptr->map_arr[col][row] == CHR_MAP_EMPTY)
		return (get_empty_img(*mlx, row, col));
	if (mlx->map_ptr->map_arr[col][row] == CHR_MAP_ITEM)
		return (get_item_img(*mlx, row, col));
	if (mlx->map_ptr->map_arr[col][row] == CHR_MAP_PLAYER)
		return (get_player_img(*mlx));
	if (mlx->map_ptr->map_arr[col][row] == CHR_MAP_GOAL)
		return (mlx->img_ptr->goal);
	error_exit("Can't find img_ptr");
}

int	null_check_for_map_img(t_map_img *img)
{
	if (!img->player_right || !img->player_left)
		return (FAIL);
	if (!img->goal || !img->wall)
		return (FAIL);
	if (!img->empty1 || !img->empty2 || !img->empty3 || !img->empty4)
		return (FAIL);
	if (!img->item1 || !img->item2)
		return (FAIL);
	return (PASS);
}
