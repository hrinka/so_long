/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_screen_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

int	draw_step_counter(t_mlx_vars *mlx)
{
	char	*step;

	step = convert_u_to_base(mlx->player->cnt_step, 10, 0);
	if (!step)
		error_exit_b("[Fail] Fail to malloc for reading step count.", mlx);
	mlx_string_put(mlx->mlx, mlx->win, 10, 15, 0xFFFFFF, "Step:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 15, 0xFFFFFF, step);
}

int	draw_game_screen_b(t_mlx_vars *mlx)
{
	int		y;
	int		x;
	void	*img_ptr;

	y = 0;
	while (y < mlx->map->size_y)
	{
		x = 0;
		while (x < mlx->map->size_x)
		{
			img_ptr = get_img_ptr_b(mlx, y, x);
			if (!img_ptr)
				return (FAIL);
			put_img_b(mlx, img_ptr, y, x);
			x++;
		}
		y++;
	}
	return (PASS);
}

int	check_to_can_move_next_pos_b(t_mlx_vars *mlx, int dy, int dx)
{
	const int	next_y = (int)mlx->player->pos_y + dy;
	const int	next_x = (int)mlx->player->pos_x + dx;
	char		next_pos;

	if (next_y < 0 || mlx->map->size_y < next_y)
		return (FAIL);
	if (next_x < 0 || mlx->map->size_x < next_x)
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

static void	move_player_and_redraw_b(t_mlx_vars *mlx)
{
	const int	pos_x = (int)mlx->player->pos_x;
	const int	pos_y = (int)mlx->player->pos_y;
	const int	next_x = (int)mlx->player->next_x;
	const int	next_y = (int)mlx->player->next_y;

	if (pos_x < next_x)
		mlx->player->is_player_facing_r = true;
	else if (pos_x > next_x)
		mlx->player->is_player_facing_r = false;
	put_img_b(mlx, get_player_img_b(*mlx), next_y, next_x);
	put_img_b(mlx, get_empty_img_b(*mlx, pos_y, pos_x), pos_y, pos_x);
	mlx->map->map_arr[next_y][next_x] = CHR_PLAYER;
	mlx->map->map_arr[pos_y][pos_x] = CHR_EMPTY;
	mlx->player->pos_x = next_x;
	mlx->player->pos_y = next_y;
}

void	player_move_and_check_fin(t_mlx_vars *mlx, int dy, int dx)
{
	char	next_pos;

	if (check_to_can_move_next_pos_b(mlx, dy, dx) == FAIL)
		return ;
	mlx->player->next_y = (int)mlx->player->pos_y + dy;
	mlx->player->next_x = (int)mlx->player->pos_x + dx;
	next_pos = mlx->map->map_arr[mlx->player->next_y][mlx->player->next_x];
	mlx->player->cnt_step++;
	if (mlx->player->cnt_step >= INT_MAX)
		error_exit_b("Step counter reach the upper limit.", mlx);
	if (next_pos == CHR_GOAL && mlx->player->can_exit)
		mlx->is_game_end = true;
	if (next_pos == CHR_ITEM)
	{
		mlx->player->cnt_item++;
		mlx->player->flg_get_item = true;
		if (mlx->player->cnt_item == mlx->map->cnt_item)
			mlx->player->can_exit = true;
	}
	move_player_and_redraw_b(mlx);
	draw_step_counter(mlx);
	print_step_to_stdout_b(mlx);
	if (mlx->is_game_end)
		close_window_b(mlx);
}
