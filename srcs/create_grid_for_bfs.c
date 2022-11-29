/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:35:31 by takira            #+#    #+#             */
/*   Updated: 2022/11/28 15:35:33 by takira           ###   ########.fr       */
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
