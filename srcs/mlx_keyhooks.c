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

static int	key_hook_and_print_step(int keycode, t_mlx_vars *mlx)
{
	if (keycode == KEY_ESC)
		return (close_window(mlx));
	mlx->player_ptr->next_y = mlx->player_ptr->pos_y;
	mlx->player_ptr->next_x = mlx->player_ptr->pos_x;
	if (keycode == 'w' || keycode == KEY_UP)
		mlx->player_ptr->next_y--;
	else if (keycode == 'a' || keycode == KEY_LEFT)
		mlx->player_ptr->next_x--;
	else if (keycode == 's' || keycode == KEY_DOWN)
		mlx->player_ptr->next_y++;
	else if (keycode == 'd' || keycode == KEY_RIGHT)
		mlx->player_ptr->next_x++;
	else
		return (1);
	if (can_player_move(*mlx->map_ptr, *mlx->player_ptr) == FAIL)
		return (0);
	move_pos_and_redraw(mlx, mlx->map_ptr, mlx->player_ptr);
	print_step_in_std(mlx);
	if (mlx->is_game_end)
	{
		ft_printf("### GAME CLEAR!!! :D ###\n");
		close_window(mlx);
	}
	return (0);
}

void	mlx_hooks(t_mlx_vars *mlx)
{
	const int	mask_key_press = 1L << 0;
	const int	mask_button_press = 1L << 17;

	mlx_hook(mlx->win_ptr, EVENT_KEY_PRESS, mask_key_press, \
	key_hook_and_print_step, mlx);
	mlx_hook(mlx->win_ptr, EVENT_DESTROY, mask_button_press, close_window, mlx);
	mlx_expose_hook(mlx->win_ptr, draw_game_screen, mlx);
}
