/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_top_screen_info_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:11:23 by takira            #+#    #+#             */
/*   Updated: 2022/12/01 10:11:24 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	clear_msg(t_mlx_vars *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < Y_OFFSET)
	{
		x = 0;
		while (x < IMAGE_SIZE * 3)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, C_TOP_CLEAR);
			x++;
		}
		y++;
	}
}

static int	draw_step_counter(t_mlx_vars *mlx)
{
	char		*step_cnt_str;

	step_cnt_str = convert_u_to_base(mlx->player->cnt_step, 10, 0);
	if (!step_cnt_str)
		err_exit_b(\
		"[Fail] Fail to malloc for reading step_cnt_str count.", mlx);
	mlx_string_put(\
	mlx->mlx, mlx->win, X_TOP_MSG, Y_TOP_MSG, C_TOP_MSG, "Step");
	mlx_string_put(\
	mlx->mlx, mlx->win, X_TOP_STEP, Y_TOP_STEP, C_TOP_STEP, step_cnt_str);
	free(step_cnt_str);
}

static int	draw_end_msg(t_mlx_vars *mlx)
{
	char	*msg;

	if (mlx->is_game_end)
		msg = "YOU WIN :D";
	else
		msg = "GAME OVER :X";
	mlx_string_put(\
	mlx->mlx, mlx->win, X_TOP_END_MSG, Y_TOP_END_MSG, C_TOP_END_MSG, msg);
}

int	draw_top_screen_info(t_mlx_vars *mlx)
{
	clear_msg(mlx);
	if (!mlx->is_game_end && !mlx->is_game_over)
		draw_step_counter(mlx);
	else
		draw_end_msg(mlx);
}
