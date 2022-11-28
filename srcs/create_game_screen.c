/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:03:40 by takira            #+#    #+#             */
/*   Updated: 2022/11/27 08:03:59 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

int	draw_game_screen(t_mlx_vars *mlx)
{
	int		row;
	int		col;
	void	*img_ptr;

	col = 0;
	while (col < mlx->map_ptr->size_col)
	{
		row = 0;
		while (row < mlx->map_ptr->size_row)
		{
			img_ptr = get_img_ptr(mlx, row, col);
			put_img(mlx, img_ptr, row, col);
			row++;
		}
		col++;
	}
	return (0);
}

int	can_player_move(t_map_info map, t_player player)
{
	const int	ny = player.next_y;
	const int	nx = player.next_x;

	if (ny < 0 || map.size_col < ny)
		return (FAIL);
	if (nx < 0 || map.size_row < nx)
		return (FAIL);
	if (map.map_arr[ny][nx] == map.chr_wall)
		return (FAIL);
	if (map.map_arr[ny][nx] == map.chr_exit && !player.can_exit)
		return (FAIL);
	return (PASS);
}

static void	redraw_move_player(t_mlx_vars *mlx)
{
	void		*player_img;
	const int	pos_x = mlx->player_ptr->pos_x;
	const int	pos_y = mlx->player_ptr->pos_y;
	const int	next_x = mlx->player_ptr->next_x;
	const int	next_y = mlx->player_ptr->next_y;

	if (pos_x < next_x)
		mlx->player_ptr->is_facing_right = true;
	else if (pos_x > next_x)
		mlx->player_ptr->is_facing_right = false;
	player_img = get_player_img(*mlx);
	put_img(mlx, player_img, next_x, next_y);
	put_img(mlx, get_empty_img(*mlx), pos_x, pos_y);
}

void	move_pos_and_redraw(t_mlx_vars *mlx, t_map_info *map, t_player *player)
{
	const char	next_pos = map->map_arr[player->next_y][player->next_x];

	if (next_pos == map->chr_exit && !player->can_exit)
		return ;
	player->cnt_step++;
	if (next_pos == map->chr_exit && player->can_exit)
		mlx->is_game_end = true;
	if (next_pos == map->chr_item)
	{
		player->cnt_item++;
		player->flg_get_item = true;
		if (player->cnt_item == map->cnt_item)
			player->can_exit = true;
	}
	redraw_move_player(mlx);
	map->map_arr[player->next_y][player->next_x] = map->chr_player;
	map->map_arr[player->pos_y][player->pos_x] = map->chr_empty;
	player->pos_x = player->next_x;
	player->pos_y = player->next_y;
}
