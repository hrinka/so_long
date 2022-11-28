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

void	*get_empty_img(t_mlx_vars mlx)
{
	return (mlx.img_ptr->empties[rand() % get_map_kinds(mlx.img_ptr->empties)]);
}

void	*get_item_img(t_mlx_vars mlx)
{
	return (mlx.img_ptr->items[rand() % get_map_kinds(mlx.img_ptr->items)]);
}

void	*get_img_ptr(t_mlx_vars *mlx, int row, int col)
{
	if (mlx->map_ptr->map_arr[col][row] == mlx->map_ptr->chr_wall)
		return (mlx->img_ptr->wall);
	if (mlx->map_ptr->map_arr[col][row] == mlx->map_ptr->chr_empty)
		return (get_empty_img(*mlx));
	if (mlx->map_ptr->map_arr[col][row] == mlx->map_ptr->chr_item)
		return (get_item_img(*mlx));
	if (mlx->map_ptr->map_arr[col][row] == mlx->map_ptr->chr_player)
		return (get_player_img(*mlx));
	if (mlx->map_ptr->map_arr[col][row] == mlx->map_ptr->chr_exit)
		return (mlx->img_ptr->goal);
	error_exit("Fail to get img_ptr");
}

int	valid_map_img(t_map_img *img)
{
	size_t	i;

	if (!img->player_right || !img->player_left)
		return (FAIL);
	if (!img->goal || !img->wall)
		return (FAIL);
	if (!img->empties || !img->items)
		return (FAIL);
	i = 0;
	while (img->empties[i])
		if (!img->empties[i++])
			return (FAIL);
	i = 0;
	while (img->items[i])
		if (!img->items[i++])
			return (FAIL);
	return (PASS);
}
