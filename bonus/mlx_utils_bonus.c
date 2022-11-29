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

void	*xpm_to_img_ptr(t_mlx_vars mlx, char *filepath)
{
	int		width;
	int		height;
	void	*ret_img_ptr;

	ret_img_ptr = mlx_xpm_file_to_image(mlx.mlx, \
	filepath, &width, &height);
	return (ret_img_ptr);
}

void	put_img(t_mlx_vars *mlx, void *img_ptr, size_t y, size_t x)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, \
	img_ptr, (int)x * IMAGE_SIZE, (int)y * IMAGE_SIZE);
}

static int	destroy_img_ptr(t_mlx_vars *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img->player_right);
	mlx_destroy_image(mlx->mlx, mlx->img->player_left);
	mlx_destroy_image(mlx->mlx, mlx->img->goal);
	mlx_destroy_image(mlx->mlx, mlx->img->wall);
	mlx_destroy_image(mlx->mlx, mlx->img->item1);
	mlx_destroy_image(mlx->mlx, mlx->img->item2);
	mlx_destroy_image(mlx->mlx, mlx->img->empty1);
	mlx_destroy_image(mlx->mlx, mlx->img->empty2);
	mlx_destroy_image(mlx->mlx, mlx->img->empty3);
	mlx_destroy_image(mlx->mlx, mlx->img->empty4);
	return (0);
}

int	mlx_destroys(t_mlx_vars *mlx)
{
	destroy_img_ptr(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_map_arr(mlx->map, 0);
	free(mlx->mlx);
	return (0);
}

int	close_window(t_mlx_vars *mlx)
{
	if (mlx->is_game_end)
		ft_printf("### GAME CLEAR!!! :D ###\n");
	mlx_loop_end(mlx->mlx);
	return (0);
}
