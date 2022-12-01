/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

void	*xpm_to_img_ptr_b(t_mlx_vars mlx, char *filepath)
{
	int		width;
	int		height;
	void	*ret_img_ptr;

	ret_img_ptr = mlx_xpm_file_to_image(mlx.mlx, \
	filepath, &width, &height);
	return (ret_img_ptr);
}

void	put_img_b(t_mlx_vars *mlx, void *img_ptr, size_t y, size_t x)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, \
	img_ptr, (int)x * IMAGE_SIZE, (int)y * IMAGE_SIZE + Y_OFFSET);
}

int	destroy_mlx_and_map_b(t_mlx_vars *mlx)
{
	if (!mlx)
		return (1);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	destroy_img_ptr_b(mlx);
	free_map_arr_b(mlx->map, 0);
	free_alloc_img_arr_b(mlx->img);
	free(mlx->mlx);
	return (0);
}

int	print_std_msg_and_loop_end_b(t_mlx_vars *mlx)
{
	if (mlx->is_game_end)
		ft_printf("### GAME CLEAR :D ###\n");
	if (mlx->is_game_over)
		ft_printf("### GAME OVER :X ###\n");
	mlx_loop_end(mlx->mlx);
	exit(EXIT_SUCCESS);
}
