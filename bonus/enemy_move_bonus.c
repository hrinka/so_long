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

void	print_bfs_b(int **grid, t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			ft_printf("% .02d ", grid[i][j++]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n");
}

static int	get_next_pos(int **grid, t_enemy *e, t_map_param *map)
{
	int			i;
	int			min_idx;
	int			min_value;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	i = 0;
	min_value = INT_MAX;
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
	if (min_value == INT_MAX)
		return (FAIL);
	printf("    # get_next_pos\n");
	printf("    # (%d, %d)->(%d, %d)\n", e->pos_y, e->pos_x, e->pos_y+d[min_idx][0], e->pos_x+d[min_idx][1]);
	e->ny = e->pos_y + d[min_idx][0];
	e->nx = e->pos_x + d[min_idx][1];
	return (PASS);
}

static void	move_enemy_and_redraw_b(t_mlx_vars *mlx, t_enemy *enemy)
{
	const int	pos_x = enemy->pos_x;
	const int	pos_y = enemy->pos_y;
	const int	next_x = enemy->nx;
	const int	next_y = enemy->ny;

	printf("       # move and redraw 1\n");
	if (pos_x < next_x)
		enemy->is_enemy_facing_r = true;
	else if (pos_x > next_x)
		enemy->is_enemy_facing_r = false;
	printf("       # move and redraw 2\n");
	put_img_b(mlx, get_enemy_img_b(*mlx, enemy->flame + 1, enemy->is_enemy_facing_r), next_y, next_x);
	printf("       # move and redraw 3\n");
	put_img_b(mlx, get_empty_img_b(*mlx, pos_y, pos_x), pos_y, pos_x);
	printf("       # move and redraw 4\n");
	mlx->map->map_arr[next_y][next_x] = CHR_ENEMY;
	printf("       # move and redraw 5\n");
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	printf("       # move and redraw (y, x) = (%d, %d) -> (%d, %d)\n", pos_y, pos_x, next_y, next_x);
	enemy->pos_x = next_x;
	enemy->pos_y = next_y;
	if (mlx->map->map_arr[next_y][next_x] == CHR_PLAYER)
		mlx->is_game_over = true;
}

int	enemy_move_and_check_fin(t_mlx_vars *mlx, t_map_param *map)
{
	int	enemy_no;
	int	**bfs_grid;

	print_map_b(*mlx->map, "enemy_move_and_check_fin");

	bfs_grid = create_bfs_grid_b(map->map_arr, \
	(int) map->size_y, (int) map->size_x, true);
	if (!bfs_grid)
		return (FAIL);
	bfs_b(bfs_grid, *map, (int)mlx->player->pos_y, (int)mlx->player->pos_x);
//	print_bfs_b(bfs_grid, map, "bfs in animation");
	enemy_no = 0;
	printf("\n #enemy move and check fin no:%d, cnt:%d\n", enemy_no, (int)mlx->map->cnt_enemy);
	while (enemy_no < mlx->map->cnt_enemy)
	{
		printf("   #enemyno:%d, (y,x)=(%d, %d)\n", enemy_no, mlx->player->enemy[enemy_no].pos_y, mlx->player->enemy[enemy_no].pos_x);
		if (enemy_no % 2 == mlx->enemy_move_no)
			if (get_next_pos(bfs_grid, &mlx->player->enemy[enemy_no], map) == PASS)
				move_enemy_and_redraw_b(mlx, &mlx->player->enemy[enemy_no]);
		if (mlx->is_game_over)
			break ;
		enemy_no++;
	}
	free_grid_b(bfs_grid, map->size_y);
	if (mlx->is_game_over)
		close_window_b(mlx);
	return (PASS);
}
