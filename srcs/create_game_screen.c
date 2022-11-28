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
	while (col < mlx->map->size_col)
	{
		row = 0;
		while (row < mlx->map->size_row)
		{
			img_ptr = get_img_ptr(mlx, row, col);
			put_img(mlx, img_ptr, row, col);
			row++;
		}
		col++;
	}
	return (0);
}

int	check_to_can_move_next_pos(t_mlx_vars *mlx, int dy, int dx)
{
	const int	next_y = mlx->player->pos_y + dy;
	const int	next_x = mlx->player->pos_x + dx;
	char		next_pos;

	if (next_y < 0 || mlx->map->size_col < next_y)
		return (FAIL);
	if (next_x < 0 || mlx->map->size_row < next_x)
		return (FAIL);
	if (mlx->map->map_arr[next_y][next_x] == CHR_WALL)
		return (FAIL);
	if (mlx->map->map_arr[next_y][next_x] == CHR_GOAL && !mlx->player->can_exit)
		return (FAIL);
	next_pos = mlx->map->map_arr[mlx->player->next_y][mlx->player->next_x];
	if (next_pos == CHR_GOAL && !mlx->player->can_exit)
		return (FAIL);
	return (PASS);
}

static void	move_player_and_redraw(t_mlx_vars *mlx)
{
	const int	pos_x = mlx->player->pos_x;
	const int	pos_y = mlx->player->pos_y;
	const int	next_x = mlx->player->next_x;
	const int	next_y = mlx->player->next_y;

	if (pos_x < next_x)
		mlx->player->is_facing_right = true;
	else if (pos_x > next_x)
		mlx->player->is_facing_right = false;
	put_img(mlx, get_player_img(*mlx), next_x, next_y);
	put_img(mlx, get_empty_img(*mlx, pos_x, pos_y), pos_x, pos_y);
	mlx->map->map_arr[next_y][next_x] = CHR_PLAYER;
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	mlx->player->pos_x = next_x;
	mlx->player->pos_y = next_y;
}

void	move_and_judge_finish(t_mlx_vars *mlx, int dy, int dx)
{
	char		next_pos;

	if (check_to_can_move_next_pos(mlx, dy, dx) == FAIL)
		return ;
	mlx->player->next_y = mlx->player->pos_y + dy;
	mlx->player->next_x = mlx->player->pos_x + dx;
	next_pos = mlx->map->map_arr[mlx->player->next_y][mlx->player->next_x];
	mlx->player->cnt_step++;
	if (mlx->player->cnt_step >= INT_MAX)
		error_exit("Step counter will be overflow.");
	if (next_pos == CHR_GOAL && mlx->player->can_exit)
		mlx->is_game_end = true;
	if (next_pos == CHR_ITEM)
	{
		mlx->player->cnt_item++;
		mlx->player->flg_get_item = true;
		if (mlx->player->cnt_item == mlx->map->cnt_item)
			mlx->player->can_exit = true;
	}
	move_player_and_redraw(mlx);
	print_step_or_finish_to_stdout(mlx);
}
