/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_img_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:51:52 by takira            #+#    #+#             */
/*   Updated: 2023/05/30 23:42:22 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	init_player_img_b(t_mlx_vars *mlx, t_img *img)
{
	img->players = (void **)ft_calloc(sizeof(void *), CNT_PLAYER_FLM * 2 + 1);
	if (!img->players)
		return (FAIL);
	img->players[0] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_R1);
	img->players[1] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_R2);
	img->players[2] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_R3);
	img->players[3] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_R4);
	img->players[4] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_R5);
	img->players[5] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_L1);
	img->players[6] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_L2);
	img->players[7] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_L3);
	img->players[8] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_L4);
	img->players[9] = xpm_to_img_ptr_b(*mlx, IMG_PLAYER_L5);
	img->players[10] = NULL;
	return (PASS);
}

static int	init_enemy_img_b(t_mlx_vars *mlx, t_img *img)
{
	img->enemies = (void **)ft_calloc(sizeof(void *), CNT_ENEMY_FLM * 2 + 1);
	if (!img->enemies)
		return (FAIL);
	img->enemies[0] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R1);
	img->enemies[1] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R2);
	img->enemies[2] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R3);
	img->enemies[3] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R4);
	img->enemies[4] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R5);
	img->enemies[5] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R6);
	img->enemies[6] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_R7);
	img->enemies[7] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L1);
	img->enemies[8] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L2);
	img->enemies[9] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L3);
	img->enemies[10] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L4);
	img->enemies[11] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L5);
	img->enemies[12] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L6);
	img->enemies[13] = xpm_to_img_ptr_b(*mlx, IMG_ENEMY_L7);
	img->enemies[14] = NULL;
	return (PASS);
}

static int	init_empties_and_items_img_b(t_mlx_vars *mlx, t_img *img)
{
	img->empties = (void **)ft_calloc(sizeof(void *), CNT_EMPTY + 1);
	img->items = (void **)ft_calloc(sizeof(void *), CNT_ITEM + 1);
	if (!img->empties || !img->items)
		return (FAIL);
	img->empties[0] = xpm_to_img_ptr_b(*mlx, IMG_EMPTY_1);
	img->empties[1] = xpm_to_img_ptr_b(*mlx, IMG_EMPTY_2);
	img->empties[2] = xpm_to_img_ptr_b(*mlx, IMG_EMPTY_3);
	img->empties[3] = xpm_to_img_ptr_b(*mlx, IMG_EMPTY_4);
	img->empties[4] = NULL;
	img->items[0] = xpm_to_img_ptr_b(*mlx, IMG_ITEM_1);
	img->items[1] = xpm_to_img_ptr_b(*mlx, IMG_ITEM_2);
	img->items[2] = xpm_to_img_ptr_b(*mlx, IMG_ITEM_3);
	img->items[3] = NULL;
	return (PASS);
}

int	null_check_for_map_img_b(t_img *img)
{
	size_t	i;

	i = 0;
	if (img->players)
		while (i < CNT_PLAYER_FLM * 2)
			if (!img->players[i++])
				return (FAIL);
	i = 0;
	if (img->enemies)
		while (i < CNT_ENEMY_FLM * 2)
			if (!img->enemies[i++])
				return (FAIL);
	i = 0;
	if (img->empties)
		while (i < CNT_EMPTY)
			if (!img->empties[i++])
				return (FAIL);
	i = 0;
	if (img->items)
		while (i < CNT_ITEM)
			if (!img->items[i++])
				return (FAIL);
	if (!img->wall || !img->goal)
		return (FAIL);
	return (PASS);
}

int	init_map_img_b(t_mlx_vars *mlx, t_img *img)
{
	img->goal = xpm_to_img_ptr_b(*mlx, IMG_GOAL);
	img->wall = xpm_to_img_ptr_b(*mlx, IMG_WALL);
	if (!init_player_img_b(mlx, img) || !init_enemy_img_b(mlx, img) || \
	!init_empties_and_items_img_b(mlx, img) || !null_check_for_map_img_b(img))
		return (FAIL);
	return (PASS);
}
