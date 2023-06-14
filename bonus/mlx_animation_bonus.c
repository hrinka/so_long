/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_animation_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:02:16 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:02:17 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "./includes/so_long_bonus.h"

static void	*get_player_anime_img_b(t_mlx_vars mlx, size_t flame)
{
	if (mlx.player->is_player_facing_r)
		return (mlx.img->players[flame]);
	return (mlx.img->players[flame + CNT_PLAYER_FLM]);
}

static void	*get_enemy_anime_img_b(t_mlx_vars mlx, size_t flame, bool right)
{
	if (right)
		return (mlx.img->enemies[flame]);
	return (mlx.img->enemies[flame + CNT_ENEMY_FLM]);
}

static int	player_animation_b(t_mlx_vars *mlx)
{
	const size_t	y = mlx->player->pos_y;
	const size_t	x = mlx->player->pos_x;

	put_img_b(mlx, \
	get_player_anime_img_b(*mlx, mlx->player_flame % CNT_PLAYER_FLM), y, x);
	mlx->player_flame++;
	mlx->player_flame %= CNT_PLAYER_FLM;
	mlx->player_anime_flame = 0;
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
		if (enemy_no % 2 == mlx->enemy_anime_no)
		{
			y = mlx->player->enemy[enemy_no].pos_y;
			x = mlx->player->enemy[enemy_no].pos_x;
			flame = \
			(mlx->player->enemy[enemy_no].anime_flame + 1) % CNT_ENEMY_FLM;
			is_right = mlx->player->enemy[enemy_no].is_enemy_facing_r;
			put_img_b(mlx, get_enemy_anime_img_b(*mlx, flame, is_right), y, x);
			mlx->player->enemy[enemy_no].anime_flame++;
			mlx->player->enemy[enemy_no].anime_flame %= CNT_ENEMY_FLM;
		}
		enemy_no++;
	}
	mlx->enemy_anime_flame = 0;
	mlx->enemy_anime_no = (mlx->enemy_anime_no + 1) % 2;
	return (0);
}

int	animation_b(t_mlx_vars *mlx)
{
	mlx->player_anime_flame++;
	mlx->enemy_anime_flame++;
	mlx->enemy_move_flame++;
	if (!mlx->is_game_over && !mlx->is_game_end)
	{
		if (mlx->player_anime_flame == FPS_PLAYER_ANIMATION)
			player_animation_b(mlx);
		if (mlx->enemy_anime_flame == FPS_ENEMY_ANIMATION)
			enemy_animation_b(mlx);
		if (mlx->enemy_move_flame == FPS_ENEMY_MOVE)
			enemy_move_and_check_fin(mlx, mlx->map);
		return (0);
	}
	if (!mlx->is_print_end)
	{
		draw_top_screen_info(mlx);
		mlx->is_print_end = true;
	}
	if (mlx->player_anime_flame == FPS_END_MSG)
		print_std_msg_and_loop_end_b(mlx);
	return (0);
}
