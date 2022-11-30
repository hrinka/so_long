/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:46:48 by takira            #+#    #+#             */
/*   Updated: 2022/11/30 15:46:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

void	destroy_img_ptr_b(t_mlx_vars *mlx)
{
	size_t	i;

	if (!mlx || !mlx->img)
		return ;
	i = 0;
	if (mlx->img->players)
		while (mlx->img->players[i])
			mlx_destroy_image(mlx->mlx, mlx->img->players[i++]);
	i = 0;
	if (mlx->img->enemies)
		while (mlx->img->enemies[i])
			mlx_destroy_image(mlx->mlx, mlx->img->enemies[i++]);
	i = 0;
	if (mlx->img->items)
		while (mlx->img->items[i])
			mlx_destroy_image(mlx->mlx, mlx->img->items[i++]);
	i = 0;
	if (mlx->img->empties)
		while (mlx->img->empties[i])
			mlx_destroy_image(mlx->mlx, mlx->img->empties[i++]);
	if (mlx->img->wall)
		mlx_destroy_image(mlx->mlx, mlx->img->wall);
	if (mlx->img->goal)
		mlx_destroy_image(mlx->mlx, mlx->img->goal);
}

void	free_alloc_img_b(t_img *img)
{
	free(img->players);
	free(img->enemies);
	free(img->empties);
	free(img->items);
}
