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

static void	print_bfsgrid_b(int **grid, t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			printf("%d ", grid[i][j++]);
		printf("\n");
		i++;
	}
	ft_printf("\n\n");
}

static int	get_next_pos(int **grid, t_enemy enemy, int *ny, int *nx)
{
	int			i;
	int			min_idx;
	int			min_value;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	i = 0;
	min_value = INT_MAX;
	while (i < 4)
	{
		if (grid[enemy.pos_y + d[i][0]][enemy.pos_x+ d[i][1]] < grid[enemy.pos_y][enemy.pos_x])
		{
			min_idx = i;
			min_value = grid[enemy.pos_y + d[i][0]][enemy.pos_x+ d[i][1]];
		}
		i++;
	}
	if (min_value == INT_MAX)
		return (FAIL);
	*ny = enemy.pos_y + d[min_idx][0];
	*nx = enemy.pos_y + d[min_idx][1];
	return (PASS);
}

static void	move_player_and_redraw_b(t_mlx_vars *mlx)
{
	const int	pos_x = (int)mlx->player->pos_x;
	const int	pos_y = (int)mlx->player->pos_y;
	const int	next_x = (int)mlx->player->next_x;
	const int	next_y = (int)mlx->player->next_y;

	if (pos_x < next_x)
		mlx->player->is_player_facing_r = true;
	else if (pos_x > next_x)
		mlx->player->is_player_facing_r = false;
	put_img_b(mlx, get_player_img_b(*mlx), next_y, next_x);
	put_img_b(mlx, get_empty_img_b(*mlx, pos_y, pos_x), pos_y, pos_x);
	mlx->map->map_arr[next_y][next_x] = CHR_PLAYER;
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	mlx->player->pos_x = next_x;
	mlx->player->pos_y = next_y;
}

int	enemy_move_and_check_fin(t_mlx_vars *mlx, t_map_param map)
{
	int	enemy_no;
	int	**bfs_grid;
	int nx;
	int ny;

	bfs_grid = create_bfs_grid_b(map.map_arr, \
	(int) map.size_y, (int) map.size_x, true);
	if (!bfs_grid)
		return (FAIL);
	bfs_b(bfs_grid, map);
	enemy_no = 0;
	while (enemy_no < mlx->map->cnt_enemy)
	{
		enemy_no++;
		if (enemy_no % 2 != mlx->enemy_move_no)
			continue ;
		if (!get_next_pos(bfs_grid, mlx->player->enemy[enemy_no], &ny, &nx))
			continue ;

		// swap, x, y update

		// if swap to player -> game end
		mlx->is_game_over = true;
		break ;
	}
	free_grid_b(bfs_grid, map.size_y);
	if (mlx->is_game_over)
		close_window_b(mlx);
	return (PASS);
}
