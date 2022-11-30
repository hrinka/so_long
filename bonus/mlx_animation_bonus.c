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

static void	*get_player_anime_img_b(t_mlx_vars mlx, size_t flame)
{
	if (mlx.player->is_player_facing_r)
		return (mlx.img->players[flame]);
	return (mlx.img->players[flame + CNT_PLAYER_IMG]);
}

static void	*get_enemy_anime_img_b(t_mlx_vars mlx, size_t flame, bool right)
{
	if (right)
		return (mlx.img->enemies[flame]);
	return (mlx.img->enemies[flame + CNT_ENEMY_IMG]);
}

static int	player_animation_b(t_mlx_vars *mlx)
{
	const size_t	y = mlx->player->pos_y;
	const size_t	x = mlx->player->pos_x;

	put_img_b(mlx, \
	get_player_anime_img_b(*mlx, mlx->player_flame % CNT_PLAYER_IMG), y, x);
	return (0);
}

static int	enemy_animation_b(t_mlx_vars *mlx)
{
	int		enemy_no;
	int		y;
	int		x;
	int		flame;
	bool	is_right;

	enemy_no = 0;
	while (enemy_no < mlx->map->cnt_enemy)
	{
		enemy_no++;
		if (enemy_no % 2 != mlx->enemy_anime_no)
			continue ;
		y = mlx->player->enemy[enemy_no].pos_y;
		x = mlx->player->enemy[enemy_no].pos_x;
		flame = mlx->player->enemy[enemy_no].flame % CNT_ENEMY_IMG;
		is_right = mlx->player->enemy[enemy_no].is_enemy_facing_r;
		put_img_b(mlx, get_enemy_anime_img_b(*mlx, flame, is_right), y, x);
		mlx->player->enemy[enemy_no].flame++;
		mlx->player->enemy[enemy_no].flame %= CNT_EMPTY_IMG;
	}
	return (0);
}

int	animation_b(t_mlx_vars *mlx)
{
	const int	player_anime_flame = 15000;
	const int	enemy_anime_flame = 4000;
	const int	enemy_move_flame = 1000000;

	mlx->player_anime_flame++;
	mlx->enemy_anime_flame++;
	mlx->enemy_move_flame++;
	if (mlx->player_anime_flame == player_anime_flame)
	{
		player_animation_b(mlx);
		mlx->player_flame++;
		mlx->player_flame %= CNT_PLAYER_IMG;
		mlx->player_anime_flame = 0;
	}
	if (mlx->enemy_anime_flame == enemy_anime_flame)
	{
		enemy_animation_b(mlx);
		mlx->enemy_anime_flame = 0;
		mlx->enemy_anime_no = (mlx->enemy_anime_no + 1) % 2;
	}
	if (mlx->enemy_anime_flame == enemy_move_flame)
	{
		enemy_move_and_check_fin(mlx, *mlx->map);
		mlx->enemy_move_flame = 0;
		mlx->enemy_move_no = (mlx->enemy_move_no + 1) % 2;
	}
	return (0);
}
