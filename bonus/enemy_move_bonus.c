/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:03:37 by takira            #+#    #+#             */
/*   Updated: 2022/11/30 20:03:37 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	get_next_pos(int **grid, t_enemy *e, t_map_param *map)
{
	int			i;
	int			min_idx;
	int			min_value;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	i = 0;
	min_value = grid[e->pos_y][e->pos_x];
	while (i < 4)
	{
		if (grid[e->pos_y + d[i][0]][e->pos_x + d[i][1]] != -1 && \
		grid[e->pos_y + d[i][0]][e->pos_x + d[i][1]] < min_value && \
		map->map_arr[e->pos_y + d[i][0]][e->pos_x + d[i][1]] != CHR_ENEMY && \
		map->map_arr[e->pos_y + d[i][0]][e->pos_x + d[i][1]] != CHR_ITEM)
		{
			min_idx = i;
			min_value = grid[e->pos_y + d[i][0]][e->pos_x + d[i][1]];
		}
		i++;
	}
	if (min_value == grid[e->pos_y][e->pos_x])
		return (FAIL);
	e->ny = e->pos_y + d[min_idx][0];
	e->nx = e->pos_x + d[min_idx][1];
	return (PASS);
}

static void	redraw_enemy_check_fin_b(t_mlx_vars *mlx, t_enemy *enemy)
{
	const int	pos_x = enemy->pos_x;
	const int	pos_y = enemy->pos_y;
	const int	next_x = enemy->nx;
	const int	next_y = enemy->ny;

	if (pos_x < next_x)
		enemy->is_enemy_facing_r = true;
	else if (pos_x > next_x)
		enemy->is_enemy_facing_r = false;
	put_img_b(mlx, \
	get_enemy_img_b(*mlx, enemy->anime_flame + 1, enemy->is_enemy_facing_r), \
	next_y, next_x);
	put_img_b(mlx, get_empty_img_b(*mlx, pos_y, pos_x), pos_y, pos_x);
	if (mlx->map->map_arr[next_y][next_x] == CHR_PLAYER)
		mlx->is_game_over = true;
	mlx->map->map_arr[next_y][next_x] = CHR_ENEMY;
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	enemy->pos_x = next_x;
	enemy->pos_y = next_y;
}

int	enemy_move_and_check_fin(t_mlx_vars *mlx, t_map_param *map)
{
	int	enemy_no;
	int	**bfs_grid;

	bfs_grid = create_bfs_grid_b(map->map_arr, \
	(int) map->size_y, (int) map->size_x, true);
	if (!bfs_grid)
		return (FAIL);
	bfs_b(bfs_grid, *map, (int)mlx->player->pos_y, (int)mlx->player->pos_x);
	enemy_no = 0;
	while (enemy_no < mlx->map->cnt_enemy)
	{
		if (enemy_no % 2 == mlx->enemy_move_no)
			if (get_next_pos(bfs_grid, &mlx->player->enemy[enemy_no], map))
				redraw_enemy_check_fin_b(mlx, &mlx->player->enemy[enemy_no]);
		if (mlx->is_game_over)
			break ;
		enemy_no++;
	}
	free_grid_b(bfs_grid, map->size_y);
	mlx->enemy_move_flame = 0;
	mlx->enemy_move_no = (mlx->enemy_move_no + 1) % 2;
	return (PASS);
}
