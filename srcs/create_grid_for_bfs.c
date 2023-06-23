/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid_for_bfs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:00:19 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:20:53 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

void	free_grid(int **grid, size_t y)
{
	size_t	i;

	i = 0;
	while (i < y)
		free(grid[i++]);
	free(grid);
}

static int	**create_grid(size_t y, size_t x)
{
	int		**grid;
	size_t	i;

	grid = (int **)ft_calloc(y, sizeof(int *));
	if (!grid)
		return (FAIL);
	i = 0;
	while (i < y)
	{
		grid[i] = (int *)ft_calloc(x, sizeof(int));
		if (!grid[i])
		{
			free_grid(grid, y);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

int	**create_visited(char **map_arr, size_t y, size_t x)
{
	int		**visited;
	size_t	i;
	size_t	j;

	visited = create_grid(y, x);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (map_arr[i][j] == CHR_WALL || map_arr[i][j] == CHR_GOAL)
				visited[i][j] = 2;
			j++;
		}
		i++;
	}
	return (visited);
}
