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

static void	*get_player_animation_img_b(t_mlx_vars mlx, size_t flame)
{
	if (mlx.player->is_player_facing_r)
		return (mlx.img->players[flame]);
	return (mlx.img->players[flame + CNT_PLAYER_IMG]);
}

static void	*get_enemy_animation_img_b(t_mlx_vars mlx, size_t flame)
{
	if (mlx.player->is_enemy_facing_r)
		return (mlx.img->enemies[flame]);
	return (mlx.img->enemies[flame + CNT_ENEMY_IMG]);
}

int animation_b(t_mlx_vars *mlx)
{
	const int	player_flame = 15000;
	const int	enemy_flame = 4000;

	mlx->player_animation_cnt++;
	mlx->enemy_animation_cnt++;
	if (mlx->player_animation_cnt == player_flame)
		player_animation_b(mlx);
	if (mlx->enemy_animation_cnt == enemy_flame)
		enemy_animation_b(mlx);
	return (0);
}

int	player_animation_b(t_mlx_vars *mlx)
{
	const size_t	y = mlx->player->pos_y;
	const size_t	x = mlx->player->pos_x;

	put_img_b(mlx, get_player_animation_img_b(\
	*mlx, mlx->player_flame % CNT_PLAYER_IMG), y, x);
	mlx->player_flame++;
	mlx->player_flame %= CNT_PLAYER_IMG;
	mlx->player_animation_cnt = 0;
	return (0);
}

int	enemy_animation_b(t_mlx_vars *mlx)
{
	int	enemy_no;
	int y;
	int x;
	int flame;

	enemy_no = 0;
	while (enemy_no < mlx->map->cnt_enemy)
	{
		if (enemy_no % 2 == mlx->enemy_move_no)
		{
			y = mlx->player->enemy[enemy_no].pos_y;
			x = mlx->player->enemy[enemy_no].pos_x;
			printf("no:%d, (y, x)=(%d, %d)\n",enemy_no, y, x);
			flame = mlx->player->enemy[enemy_no].flame % CNT_ENEMY_IMG;
			put_img_b(mlx, get_enemy_animation_img_b(*mlx, flame), y, x);
			mlx->player->enemy[enemy_no].flame++;
			mlx->player->enemy[enemy_no].flame %= CNT_EMPTY_IMG;
		}
		enemy_no++;
	}
	mlx->enemy_animation_cnt = 0;
	mlx->enemy_move_no = (mlx->enemy_move_no + 1) % 2;
	return (0);
}
