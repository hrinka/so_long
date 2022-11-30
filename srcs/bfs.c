/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:19 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 10:10:22 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"
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
static void	que_free(t_queue **que)
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

static t_queue	*que_last(t_queue *que)
{
	if (!que)
		return (NULL);
	while (que->next)
		que = que->next;
	return (que);
}

static void	que_append(t_queue **que, int new_y, int new_x)
{
	t_queue	*new_node;
	t_queue	*last;

	new_node = (t_queue *)malloc(sizeof(t_queue));
	if (!new_node)
	{
		que_free(que);
		error_exit("Fail to malloc in bfs.", NULL);
	}
	new_node->y = new_y;
	new_node->x = new_x;
	new_node->next = NULL;
	if (*que == NULL)
		*que = new_node;
	else
	{
		last = que_last(*que);
		last->next = new_node;
	}
}

static void	*que_pop(t_queue **que, int *y, int *x)
{
	t_queue	*next;

	if (!que || !*que)
		return (NULL);
	*y = (*que)->y;
	*x = (*que)->x;
	next = (*que)->next;
	free(*que);
	*que = next;
}

void	bfs(int **visited, t_map_param map)
{
	t_queue		*que;
	int			i;
	int			pop_x;
	int			pop_y;
	const int	d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	que = NULL;
	que_append(&que, (int)map.start_y, (int)map.start_x);
	while (que)
	{
		que_pop(&que, &pop_y, &pop_x);
		visited[pop_y][pop_x] = 1;
		i = 0;
		while (i < 4)
		{
			if ((0 < pop_y + d[i][0]) && (pop_y + d[i][0] < map.size_y - 1) && \
			(0 < pop_x + d[i][1]) && (pop_x + d[i][1] < map.size_x - 1) && \
			visited[pop_y + d[i][0]][pop_x + d[i][1]] == 0)
			{
				que_append(&que, pop_y + d[i][0], pop_x + d[i][1]);
				visited[pop_y + d[i][0]][pop_x + d[i][1]] = 1;
			}
			i++;
		}
	}
}
