/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_maps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:09:16 by takira            #+#    #+#             */
/*   Updated: 2022/11/26 19:09:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static int	valid_map(t_map_info *map)
{
	size_t			col;
	const size_t	size_row = map->size_row;
	const size_t	size_col = map->size_col;

	if (size_row < 2 || 66 < size_row || size_col < 2 || 36 < size_col)
		return (FAIL);
	if (size_row == size_col)
		return (FAIL);
	col = 0;
	while (col < size_col)
	{
		if ((col == 0 || col + 1 == size_col) && \
		cnt_chr_in_str(CHR_WALL, map->map_arr[col]) != size_row)
			return (FAIL);
		if (map->map_arr[col][0] != CHR_WALL)
			return (FAIL);
		if (map->map_arr[col][size_row - 1] != CHR_WALL)
			return (FAIL);
		if (ft_strlen_sl(map->map_arr[col]) != size_row)
			return (FAIL);
		col++;
	}
	return (PASS);
}

static int	create_map_arr(char *path, t_map_info *map)
{
	int		fd;
	char	*line;
	size_t	col;

	map->map_arr = (char **)malloc(sizeof(char *) * (map->size_col + 1));
	if (!map->map_arr)
		return (FAIL);
	fd = open(path, O_RDONLY);
	col = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		map->map_arr[col] = line;
		col++;
	}
	map->map_arr[col] = NULL;
	free(line);
	close(fd);
	return (PASS);
}

static void	count_elems(const char *line, t_map_info *map)
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
		else if (line[i] == CHR_GOAL)
			map->cnt_exit++;
		else if (line[i] != CHR_WALL && line[i] != CHR_EMPTY)
			map->cnt_others++;
		i++;
	}
	if (map->size_row == 0)
		map->size_row = i;
}

static int	get_params_frm_mapfile(const char *path, t_map_info *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		count_elems(line, map);
		if (map->start_y == 0 && map->cnt_start)
			map->start_y = map->size_col;
		map->size_col++;
		free(line);
	}
	free(line);
	close(fd);
	if (errno == 0)
		return (PASS);
	return (FAIL);
}

int	read_and_valid_maps(char *path, t_map_info *map)
{
	init_mapinfo(map);
	if (get_params_frm_mapfile(path, map) == FAIL)
		return (FAIL);
	if (map->cnt_start != 1 || map->cnt_exit != 1)
		return (FAIL);
	if (map->cnt_item == 0 || map->cnt_others > 1)
		return (FAIL);
	if (errno != 0 || create_map_arr(path, map) == FAIL)
		return (free_map_arr(map, FAIL));
	if (errno != 0 || valid_map(map) == FAIL)
		return (free_map_arr(map, FAIL));
	return (PASS);
}
