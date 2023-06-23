/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:03:03 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:22:54 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

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
/*
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
			ft_printf("%c ", map.map_arr[i][j++]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	print_bfs_b(int **grid, t_map_param map, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("\n%s\n", str);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
			ft_printf("% .02d ", grid[i][j++]);
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n");
}
*/
