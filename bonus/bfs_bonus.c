/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"
/*
static size_t que_cnt(t_queue *que)
{
	size_t	i;

	i = 0;
	while (que)
	{
		que = que->next;
		i++;
	}
	return (i);
}
*/
static void	que_free_b(t_queue **que)
{
	t_queue	*next;

	if (!que)
		return ;
	while (*que)
	{
		next = (*que)->next;
		free(*que);
		*que = next;
	}
}

static t_queue	*que_last_b(t_queue *que)
{
	if (!que)
		return (NULL);
	while (que->next)
		que = que->next;
	return (que);
}

static void	que_append_b(t_queue **que, int new_y, int new_x, int new_cnt)
{
	t_queue	*new_node;
	t_queue	*last;

	new_node = (t_queue *)malloc(sizeof(t_queue));
	if (!new_node)
	{
		que_free_b(que);
		error_exit_b("Fail to malloc in bfs.", NULL);
	}
	new_node->y = new_y;
	new_node->x = new_x;
	new_node->cnt = new_cnt;
	new_node->next = NULL;
	if (*que == NULL)
		*que = new_node;
	else
	{
		last = que_last_b(*que);
		last->next = new_node;
	}
}

static void	que_pop_b(t_queue **que, int *y, int *x, int *cnt)
{
	t_queue	*next;

	if (!que || !*que)
		return ;
	*y = (*que)->y;
	*x = (*que)->x;
	*cnt = (*que)->cnt;
	next = (*que)->next;
	free(*que);
	*que = next;
}

void	bfs_b(int **bfs_grid, t_map_param map, int sy, int sx)
{
	t_queue		*que;
	int			i;
	int			pop_x;
	int			pop_y;
	int			pop_cnt;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	que = NULL;
	que_append_b(&que, sy, sx, 0);
	while (que)
	{
		que_pop_b(&que, &pop_y, &pop_x, &pop_cnt);
		bfs_grid[pop_y][pop_x] = pop_cnt;
		i = 0;
		while (i < 4)
		{
			if ((0 < pop_y + d[i][0]) && (pop_y + d[i][0] < map.size_y - 1) && \
			(0 < pop_x + d[i][1]) && (pop_x + d[i][1] < map.size_x - 1) && \
			bfs_grid[pop_y + d[i][0]][pop_x + d[i][1]] == 0)
			{
				que_append_b(\
				&que, pop_y + d[i][0], pop_x + d[i][1], pop_cnt + 1);
				bfs_grid[pop_y + d[i][0]][pop_x + d[i][1]] = pop_cnt + 1;
			}
			i++;
		}
	}
}
