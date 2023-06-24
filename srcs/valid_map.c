/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:01:05 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/24 21:40:26 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static int	check_elems(t_map_param map, int **visited, int i, int j)
{
	int			k;
	int			path_to_goal;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	if (map.map_arr[i][j] == CHR_ITEM && visited[i][j] != 1)
		return (FAIL);
	path_to_goal = 0;
	if (map.map_arr[i][j] == CHR_GOAL)
	{
		k = 0;
		while (k < 4)
		{
			if ((0 < i + d[k][0]) && (i + d[k][0] < map.size_y - 1) && \
					(0 < j + d[k][1]) && (j + d[k][1] < map.size_x - 1) && \
					visited[i + d[k][0]][j + d[k][1]] == 1)
				path_to_goal++;
			k++;
		}
		if (path_to_goal == 0)
			return (FAIL);
	}
	return (PASS);
}

static int	check_path(t_map_param map, int **visited)
{
	ssize_t			i;
	ssize_t			j;

	i = 0;
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
		{
			if (check_elems(map, visited, i, j) == FAIL)
				return (FAIL);
			j++;
		}
		i++;
	}
	return (PASS);
}

static int	valid_path(t_map_param map)
{
	int		**visited;
	int		path_valid_result;

	visited = create_visited(map.map_arr, (int)map.size_y, (int)map.size_x);
	if (!visited)
		return (FAIL);
	bfs(visited, map);
	path_valid_result = check_path(map, visited);
	free_grid(visited, map.size_y);
	return (path_valid_result);
}

int	valid_map(t_map_param *map)
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
	if (valid_path(*map) == FAIL)
		return (FAIL);
	return (PASS);
}
