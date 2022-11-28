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

static int	valid_map(t_map_info *info)
{
	size_t	col;

	if (info->size_row < 2 || 66 < info->size_row || \
	info->size_col < 2 || 36 < info->size_col)
		return (FAIL);
	if (info->size_row == info->size_col)
		return (FAIL);
	col = 0;
	while (col < info->size_col)
	{
		if ((col == 0 || col == info->size_col - 1) && \
		cnt_chr_in_str(info->chr_wall, info->map_arr[col]) != info->size_row)
			return (FAIL);
		if (info->map_arr[col][0] != info->chr_wall)
			return (FAIL);
		if (info->map_arr[col][info->size_row - 1] != info->chr_wall)
			return (FAIL);
		if (ft_strlen_sl(info->map_arr[col]) != info->size_row)
			return (FAIL);
		col++;
	}
	return (PASS);
}

static int	create_map_arr(char *path, t_map_info *info)
{
	int		fd;
	char	*line;
	size_t	col;

	info->map_arr = (char **)malloc(sizeof(char *) * (info->size_col + 1));
	if (!info->map_arr)
		return (FAIL);
	fd = open(path, O_RDONLY);
	col = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		info->map_arr[col] = line;
		col++;
	}
	info->map_arr[col] = NULL;
	free(line);
	close(fd);
	return (PASS);
}

static void	count_elems(const char *line, t_map_info *info)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == info->chr_item)
			info->cnt_item++;
		else if (line[i] == info->chr_player)
		{
			info->cnt_start++;
			info->sx = i;
		}
		else if (line[i] == info->chr_exit)
			info->cnt_exit++;
		else if (line[i] != info->chr_wall && line[i] != info->chr_empty)
			info->cnt_others++;
		i++;
	}
	if (info->size_row == 0)
		info->size_row = i;
}

static int	get_map_params(const char *path, t_map_info *info)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		count_elems(line, info);
		if (info->sy == 0 && info->cnt_start)
			info->sy = info->size_col;
		info->size_col++;
		free(line);
	}
	free(line);
	close(fd);
	if (errno == 0)
		return (PASS);
	return (FAIL);
}

int	read_and_valid_maps(char *path, t_map_info *info)
{
	init_mapinfo(info);
	if (get_map_params(path, info) == FAIL)
		return (FAIL);
	if (info->cnt_start != 1 || info->cnt_exit != 1)
		return (FAIL);
	if (info->cnt_item == 0 || info->cnt_others > 0)
		return (FAIL);
	if (errno != 0 || create_map_arr(path, info) == FAIL)
		return (free_map_arr(info, FAIL));
	if (errno != 0 || valid_map(info) == FAIL)
		return (free_map_arr(info, FAIL));
	return (PASS);
}
