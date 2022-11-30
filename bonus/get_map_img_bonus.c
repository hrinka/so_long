/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

void	*get_player_img_b(t_mlx_vars mlx)
{
	if (mlx.player->is_facing_right)
		return (mlx.img->player_right1);
	return (mlx.img->player_left1);
}

void	*get_empty_img_b(t_mlx_vars mlx, size_t y, size_t x)
{
	if ((y + x) % 2 == 0)
		return (mlx.img->empty1);
	else if ((y + x) % 7 == 0)
		return (mlx.img->empty3);
	else if ((y + x) % 3 == 0)
		return (mlx.img->empty4);
	return (mlx.img->empty2);
}

void	*get_item_img_b(t_mlx_vars mlx, size_t y, size_t x)
{
	if ((y + x) % 2 == 0)
		return (mlx.img->item1);
	return (mlx.img->item2);
}

void	*get_img_ptr_b(t_mlx_vars *mlx, size_t y, size_t x)
{
	if (mlx->map->map_arr[y][x] == CHR_WALL)
		return (mlx->img->wall);
	if (mlx->map->map_arr[y][x] == CHR_EMPTY)
		return (get_empty_img_b(*mlx, y, x));
	if (mlx->map->map_arr[y][x] == CHR_ITEM)
		return (get_item_img_b(*mlx, y, x));
	if (mlx->map->map_arr[y][x] == CHR_PLAYER)
		return (get_player_img_b(*mlx));
	if (mlx->map->map_arr[y][x] == CHR_GOAL)
		return (mlx->img->goal);
	return (NULL);
}

int	null_check_for_map_img_b(t_img *img)
{
	if (!img->player_right1 || !img->player_left1)
		return (FAIL);
	if (!img->goal || !img->wall)
		return (FAIL);
	if (!img->empty1 || !img->empty2 || !img->empty3 || !img->empty4)
		return (FAIL);
	if (!img->item1 || !img->item2)
		return (FAIL);
	return (PASS);
}
