/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:03:08 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:03:16 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	check_elems_b(t_map_param map, int **bfs_grid, int i, int j)
{
	int			k;
	int			path_to_goal;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	if (map.map_arr[i][j] == CHR_ITEM && bfs_grid[i][j] == 0)
		return (FAIL);
	path_to_goal = 0;
	if (map.map_arr[i][j] == CHR_GOAL)
	{
		k = 0;
		while (k < 4)
		{
			if ((0 < i + d[k][0]) && (i + d[k][0] < map.size_y - 1) && \
					(0 < j + d[k][1]) && (j + d[k][1] < map.size_x - 1) && \
					bfs_grid[i + d[k][0]][j + d[k][1]] > 0)
				path_to_goal++;
			k++;
		}
		if (path_to_goal == 0)
			return (FAIL);
	}
	return (PASS);
}

static int	check_path_b(t_map_param map, int **visited)
{
	int			i;
	int			j;

	i = 0;
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
		{
			if (check_elems_b(map, visited, i, j) == FAIL)
				return (FAIL);
			j++;
		}
		i++;
	}
	return (PASS);
}

static int	valid_path_b(t_map_param map)
{
	int		**bfs_grid;
	int		path_valid_result;

	bfs_grid = create_bfs_grid_b(map.map_arr, \
	(int) map.size_y, (int) map.size_x, false);
	if (!bfs_grid)
		return (FAIL);
	bfs_b(bfs_grid, map, (int)map.start_y, (int)map.start_x);
	path_valid_result = check_path_b(map, bfs_grid);
	free_grid_b(bfs_grid, map.size_y);
	return (path_valid_result);
}

int	valid_map_b(t_map_param *map)
{
	size_t			y;
	const size_t	size_y = map->size_y;
	const size_t	size_x = map->size_x;

	if (size_y < MAP_MIN || MAP_MAX < size_y)
		return (FAIL);
	if (size_x < MAP_MIN || MAP_MAX < size_x || size_y == size_x)
		return (FAIL);
	y = 0;
	while (y < size_y)
	{
		if (ft_strlen_ns(map->map_arr[y]) != size_x)
			return (FAIL);
		if (y == 0 || y == size_y - 1)
			if (cnt_chr_in_str(CHR_WALL, map->map_arr[y]) != size_x)
				return (FAIL);
		if (map->map_arr[y][0] != CHR_WALL)
			return (FAIL);
		if (map->map_arr[y][size_x - 1] != CHR_WALL)
			return (FAIL);
		y++;
	}
	if (valid_path_b(*map) == FAIL)
		return (FAIL);
	return (PASS);
}
