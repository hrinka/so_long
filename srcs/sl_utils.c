/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:04:19 by takira            #+#    #+#             */
/*   Updated: 2022/11/27 13:04:20 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

int	err_exit(char *msg, t_mlx_vars *mlx)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
		ft_printf(" ** strerror : %s", strerror(errno));
	if (mlx)
		destroy_mlx_and_map(mlx);
	exit(EXIT_FAILURE);
}

int	free_map_arr(t_map_param *map, int ret_val)
{
	size_t	y;

	y = 0;
	if (map->map_arr)
		while (y < map->size_y)
			free(map->map_arr[y++]);
	free(map->map_arr);
	return (ret_val);
}

void	print_step_to_stdout(t_mlx_vars *mlx)
{
	const int	player_step = (int)mlx->player->cnt_step;
	const int	player_item = (int)mlx->player->cnt_item;
	const int	map_item = (int)mlx->map->cnt_item;

	if (mlx->player->flg_get_item)
	{
		ft_printf(" Step:%d  Item:%d/%d\n", player_step, player_item, map_item);
		mlx->player->flg_get_item = false;
	}
	else
		ft_printf(" Step:%d\n", player_step);
}

char	*valid_map_path_name(char *argv)
{
	char			*path;
	char			*filename;
	size_t			len;
	const size_t	ber_len = ft_strlen_ns(FILE_EXTENSION);

	path = ft_strtrim(argv, SPACES);
	if (!path)
		return (NULL);
	filename = ft_strrchr(path, '/');
	if (filename)
		filename++;
	else
		filename = path;
	len = ft_strlen_ns(filename);
	if (len <= ber_len)
	{
		free(path);
		return (NULL);
	}
	if (ft_strncmp(&filename[len - ber_len], FILE_EXTENSION, ber_len) != 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}
/*
void	print_map(t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			ft_printf("%c ", map.map_arr[i][j++]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	print_bfs(int **grid, t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			ft_printf("%d ", grid[i][j++]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n");
}
 */