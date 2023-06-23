/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:02:34 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:22:42 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static void	init_t_player_b(t_player *player, t_map_param map)
{
	player->pos_x = map.start_x;
	player->pos_y = map.start_y;
	player->next_x = (int)player->pos_x;
	player->next_y = (int)player->pos_y;
	player->cnt_step = 0;
	player->cnt_item = 0;
	player->can_exit = false;
	player->is_player_facing_r = true;
	player->flg_get_item = false;
}

static void	set_enemy_param(t_player *player, int i, int j, int k)
{
	player->enemy[k].pos_y = i;
	player->enemy[k].pos_x = j;
	player->enemy[k].ny = j;
	player->enemy[k].nx = i;
	player->enemy[k].anime_flame = 0;
	player->enemy[k].is_enemy_facing_r = true;
}

static int	get_enemy_coordinate(t_player *player, t_map_param *map)
{
	int	i;
	int	j;
	int	k;

	player->enemy = (t_enemy *)ft_calloc(sizeof(t_enemy), map->cnt_enemy + 1);
	if (!player->enemy)
		return (FAIL);
	i = 0;
	k = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map_arr[i][j] == CHR_ENEMY)
			{
				set_enemy_param(player, i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
	return (PASS);
}

static void	init_mlx_ptr_params_b(t_mlx_vars *mlx)
{
	mlx->is_game_end = false;
	mlx->is_game_over = false;
	mlx->is_print_end = false;
	mlx->player_anime_flame = 0;
	mlx->enemy_anime_flame = 0;
	mlx->enemy_move_flame = 0;
	mlx->player_flame = 0;
	mlx->enemy_anime_no = 0;
	mlx->enemy_move_no = 0;
}

void	init_mlx_ptr_b(t_mlx_vars *x, t_map_param *m, t_img *i, t_player *p)
{
	const int	size_x = (int)m->size_x * IMAGE_SIZE;
	const int	size_y = (int)m->size_y * IMAGE_SIZE + Y_OFFSET;

	x->mlx = mlx_init();
	if (!x->mlx)
		err_exit_b("[Fail] Fail to init minilibx.", NULL);
	x->win = mlx_new_window(x->mlx, size_x, size_y, "./so_long");
	if (!x->win)
		err_exit_b("[Fail] Fail to generate window.", NULL);
	x->map = m;
	x->img = i;
	x->player = p;
	init_mlx_ptr_params_b(x);
	if (init_map_img_b(x, i) == FAIL)
		err_exit_b("[Fail] Fail to get map img.", NULL);
	init_t_player_b(p, *m);
	if (get_enemy_coordinate(p, m) == FAIL)
		err_exit_b("[Fail] Fail to get enemy's info.", NULL);
}
