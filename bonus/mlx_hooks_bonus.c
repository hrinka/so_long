/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

static int	key_hook_b(int keycode, t_mlx_vars *mlx)
{
	if (keycode == KEY_ESC)
		return (close_window_b(mlx));
	if (keycode == 'w' || keycode == KEY_UP)
		player_move_and_check_fin(mlx, -1, 0);
	if (keycode == 'a' || keycode == KEY_LEFT)
		player_move_and_check_fin(mlx, 0, -1);
	if (keycode == 's' || keycode == KEY_DOWN)
		player_move_and_check_fin(mlx, 1, 0);
	if (keycode == 'd' || keycode == KEY_RIGHT)
		player_move_and_check_fin(mlx, 0, 1);
	return (0);
}

void	mlx_hooks_b(t_mlx_vars *mlx)
{
	const int	mask_key_press = 1L << 0;
	const int	mask_button_press = 1L << 17;

	mlx_hook(mlx->win, EVENT_KEY_PRESS, mask_key_press, key_hook_b, mlx);
	mlx_hook(mlx->win, EVENT_DESTROY, mask_button_press, close_window_b, mlx);
	mlx_expose_hook(mlx->win, draw_game_screen_b, mlx);
	mlx_loop_hook(mlx->mlx, animation_b, mlx);
}
