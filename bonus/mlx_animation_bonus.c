/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:45:10 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 19:45:12 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static void	*get_player_animation_img(t_mlx_vars mlx, size_t move_cnt)
{
	if (mlx.player->is_facing_right)
	{
		if (move_cnt % 5 == 0)
			return (mlx.img->player_right1);
		else if (move_cnt % 5 == 1)
			return (mlx.img->player_right2);
		else if (move_cnt % 5 == 2)
			return (mlx.img->player_right3);
		else if (move_cnt % 5 == 3)
			return (mlx.img->player_right4);
		return (mlx.img->player_right5);
	}
	if (move_cnt % 5 == 0)
		return (mlx.img->player_left1);
	else if (move_cnt % 5 == 1)
		return (mlx.img->player_left2);
	else if (move_cnt % 5 == 2)
		return (mlx.img->player_left3);
	else if (move_cnt % 5 == 3)
		return (mlx.img->player_left4);
	return (mlx.img->player_left5);
}

int	run_animation(t_mlx_vars *mlx)
{
	const size_t	y = mlx->player->pos_y;
	const size_t	x = mlx->player->pos_x;

	mlx->animation_cnt++;
	if (mlx->animation_cnt == 15000)
	{
		put_img(mlx, get_player_animation_img(*mlx, mlx->player_flame), y, x);
		mlx->animation_cnt = 0;
		mlx->player_flame++;
	}
	return (0);
}
