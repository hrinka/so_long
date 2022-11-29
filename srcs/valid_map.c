/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:22:37 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 08:22:38 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static	int **create_grid(int row, int col)
{
	int		**grid;
	size_t	i;

	grid = (int **)ft_calloc(row, sizeof(int *));
	if (!grid)
		return (FAIL);
	i = 0;
	while (i < row)
	{
		grid[i] = (int *)ft_calloc(col, sizeof(int));
		if (!grid[i])
		{
			i = 0;
			while (i < col)
				free(grid[i++]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

static int	valid_path(char **map_arr, int row, int col)
{
	int		**grid;
	size_t	i;
	size_t	j;

	grid = create_grid(row, col);
	bfs();
	check();
	return (PASS);
}

int	valid_map(t_map_param *map)
{
	size_t			row;
	const size_t	size_row = map->size_row;
	const size_t	size_col = map->size_col;

	if (size_row < 2 || 66 < size_row || size_col < 2 || 36 < size_col)
		return (FAIL);
	if (size_row == size_col)
		return (FAIL);
	row = 0;
	while (row < size_col)
	{
		if ((row == 0 || row + 1 == size_col) && \
		cnt_chr_in_str(CHR_WALL, map->map_arr[row]) != size_row)
			return (FAIL);
		if (map->map_arr[row][0] != CHR_WALL)
			return (FAIL);
		if (map->map_arr[row][size_row - 1] != CHR_WALL)
			return (FAIL);
		if (ft_strlen_ns(map->map_arr[row]) != size_row)
			return (FAIL);
		row++;
	}
	if (valid_path(map->map_arr, (int)map->size_row, (int)map->size_col) == FAIL)
		return (FAIL);
	return (PASS);
}
