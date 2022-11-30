/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

int	error_exit_b(char *msg, t_mlx_vars *mlx)
{
	ft_printf("Error\n%s\n", msg);
	if (errno != 0)
		ft_printf(" ** strerror : %s", strerror(errno));
	if (mlx)
		destroy_mlx_and_map_b(mlx);
	exit(EXIT_FAILURE);
}

int	free_map_arr_b(t_map_param *map, int ret_val)
{
	size_t	y;

	y = 0;
	if (map->map_arr)
		while (y < map->size_y)
			free(map->map_arr[y++]);
	free(map->map_arr);
	return (ret_val);
}

void	print_step_to_stdout_b(t_mlx_vars *mlx)
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

char	*valid_map_path_name_b(char *argv)
{
	char			*path;
	char			*filename;
	size_t			len;
	const size_t	ber_len = ft_strlen_ns(EXTENSION);

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
	if (ft_strncmp(&filename[len - ber_len], EXTENSION, ber_len) != 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

char	*convert_u_to_base(unsigned long u, int base, int capitals)
{
	size_t			len;
	unsigned long	num;
	char			*ret_str;
	const char		*hex_digit = "0123456789abcdef0123456789ABCDEF";

	num = u;
	len = 0;
	if (u == 0)
		len++;
	while (num > 0)
	{
		num /= base;
		len += 1;
	}
	ret_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret_str)
		return (NULL);
	ret_str[len] = '\0';
	while (len--)
	{
		ret_str[len] = hex_digit[u % base + capitals];
		u /= base;
	}
	return (ret_str);
}

void	print_map_b(t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			printf("%c ", map.map_arr[i][j++]);
		printf("\n");
		i++;
	}
	ft_printf("\n");
}

//void	print_bfs_b(int **grid, t_map_param map, char *str)
//{
//	size_t	i;
//	size_t	j;
//
//	i = 0;
//	ft_printf("\n%s\n", str);
//	while (i < map.size_y)
//	{
//		j = 0;
//		while (j < map.size_x)
//			printf("%d ", grid[i][j++]);
//		printf("\n");
//		i++;
//	}
//	ft_printf("\n\n");
//}
