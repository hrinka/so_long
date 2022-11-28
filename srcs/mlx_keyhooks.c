/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:54:48 by takira            #+#    #+#             */
/*   Updated: 2022/11/28 16:54:49 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static int	key_hook(int keycode, t_mlx_vars *mlx)
{
	if (keycode == KEY_ESC)
		return (close_window(mlx));
	if (keycode == 'w' || keycode == KEY_UP)
		move_and_judge_finish(mlx, -1, 0);
	if (keycode == 'a' || keycode == KEY_LEFT)
		move_and_judge_finish(mlx, 0, -1);
	if (keycode == 's' || keycode == KEY_DOWN)
		move_and_judge_finish(mlx, 1, 0);
	if (keycode == 'd' || keycode == KEY_RIGHT)
		move_and_judge_finish(mlx, 0, 1);
	return (0);
}

void	mlx_hooks(t_mlx_vars *mlx)
{
	const int	mask_key_press = 1L << 0;
	const int	mask_button_press = 1L << 17;

	mlx_hook(mlx->win, EVENT_KEY_PRESS, mask_key_press, key_hook, mlx);
	mlx_hook(mlx->win, EVENT_DESTROY, mask_button_press, close_window, mlx);
	mlx_expose_hook(mlx->win, draw_game_screen, mlx);
}
