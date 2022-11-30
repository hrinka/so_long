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
			flame = mlx->player->enemy[enemy_no].anime_flame % CNT_ENEMY_FLM;
			is_right = mlx->player->enemy[enemy_no].is_enemy_facing_r;
			put_img_b(mlx, get_enemy_anime_img_b(*mlx, flame, is_right), y, x);
			mlx->player->enemy[enemy_no].anime_flame++;
			mlx->player->enemy[enemy_no].anime_flame %= CNT_EMPTY;
		}
		enemy_no++;
	}
	return (0);
}

int	animation_b(t_mlx_vars *mlx)
{
	const size_t	player_anime_fps = 15000;
	const size_t	enemy_anime_fps = 4000;
	const size_t	enemy_move_fps = 100000;
	static size_t	attack_check = 1000;


	mlx->player_anime_flame++;
	mlx->enemy_anime_flame++;
	mlx->enemy_move_flame++;
	if (mlx->player_anime_flame % attack_check == 0)
	{

		if (mlx->is_game_over)
			close_window_b(mlx);
	}
	if (mlx->player_anime_flame == player_anime_fps)
	{
		player_animation_b(mlx);
		mlx->player_flame++;
		mlx->player_flame %= CNT_PLAYER_FLM;
		mlx->player_anime_flame = 0;
	}
	if (mlx->enemy_anime_flame == enemy_anime_fps)
	{
		enemy_animation_b(mlx);
		mlx->enemy_anime_flame = 0;
		mlx->enemy_anime_no = (mlx->enemy_anime_no + 1) % 2;
	}
	if (mlx->enemy_move_flame == enemy_move_fps)
	{
		print_map_b(*mlx->map, "animation");
		printf("move anime_flame:%zu, move_no:%d\n", enemy_move_fps, mlx->enemy_move_no);
		enemy_move_and_check_fin(mlx, mlx->map);
		mlx->enemy_move_flame = 0;
		mlx->enemy_move_no = (mlx->enemy_move_no + 1) % 2;
	}
//	printf("print:%zu\n", print);
//	if (print % 100000 == 0)
//		print_map_b(*mlx->map, "animation");
	return (0);
}
