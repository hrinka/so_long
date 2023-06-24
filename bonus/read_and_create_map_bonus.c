/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_create_map_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:02:50 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/24 22:31:45 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	create_map_arr_b(char *path, t_map_param *map)
{
	int		fd;
	char	*line;
	size_t	row;

	map->map_arr = (char **)malloc(sizeof(char *) * (map->size_x + 1));
	if (!map->map_arr)
		return (FAIL);
	fd = open(path, O_RDONLY);
	row = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		map->map_arr[row] = line;
		row++;
	}
	map->map_arr[row] = NULL;
	free(line);
	close(fd);
	free(path);
	return (PASS);
}

static void	count_line_elems_b(const char *line, t_map_param *map)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == CHR_ITEM)
			map->cnt_item++;
		else if (line[i] == CHR_PLAYER)
		{
			map->cnt_start++;
			map->start_x = i;
		}
		else if (line[i] == CHR_ENEMY)
			map->cnt_enemy++;
		else if (line[i] == CHR_GOAL)
			map->cnt_exit++;
		else if (line[i] != CHR_WALL && line[i] != CHR_EMPTY)
			map->cnt_others++;
		i++;
	}
	if (map->size_x == 0)
		map->size_x = i;
}

static int	read_mapfile_and_get_param_b(char *path, t_map_param *map)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;

	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		count_line_elems_b(line, map);
		if (map->start_y == 0 && map->cnt_start)
			map->start_y = map->size_y;
		map->size_y++;
		free(line);
	}
	free(line);
	close(fd);
	if (errno == 0)
		return (PASS);
	return (FAIL);
}

static void	init_map_param_b(t_map_param *map)
{
	map->map_arr = NULL;
	map->cnt_item = 0;
	map->cnt_start = 0;
	map->cnt_exit = 0;
	map->cnt_enemy = 0;
	map->cnt_others = 0;
	map->size_x = 0;
	map->size_y = 0;
	map->start_x = 0;
	map->start_y = 0;
}

int	read_and_valid_map_b(char *path, t_map_param *map)
{
	init_map_param_b(map);
	if (read_mapfile_and_get_param_b(path, map) == FAIL)
	{
		free(path);
		err_exit_b("[Fail] Fail to read file.", NULL);
	}
	if (map->cnt_start != 1 || map->cnt_exit != 1)
		err_exit_b("[Invalid map] Map must have 1 'P' and 'E'.", NULL);
	if (map->cnt_item == 0 || map->cnt_enemy == 0)
		err_exit_b("[Invalid map] Must contain at least 1 'C' and 'X'.", NULL);
	if (map->cnt_others >= 1)
		err_exit_b(\
		"[Invalid map] Has to be constructed by '0, 1, C, E, P, X'.", NULL);
	if (errno != 0 || create_map_arr_b(path, map) == FAIL)
	{
		free_map_arr_b(map, EXIT_FAILURE);
		err_exit_b("[Fail] Fail to create map arr.", NULL);
	}
	if (errno != 0 || valid_map_b(map) == FAIL)
	{
		free_map_arr_b(map, EXIT_FAILURE);
		err_exit_b("[Invalid map] Must be rectangle,\
		 closed by '1', have valid path.", NULL);
	}
	return (0);
}
