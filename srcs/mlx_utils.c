/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:25:08 by takira            #+#    #+#             */
/*   Updated: 2022/11/28 13:25:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

void	*xpm_to_img_ptr(t_mlx_vars mlx, char *filepath)
{
	int		width;
	int		height;
	void	*ret_img_ptr;

	ret_img_ptr = mlx_xpm_file_to_image(mlx.mlx_ptr, \
	filepath, &width, &height);
	return (ret_img_ptr);
}

void	put_img(t_mlx_vars *mlx, void *img_ptr, int row, int col)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
	img_ptr, row * IMAGE_SIZE, col * IMAGE_SIZE);
}

int	destroy_img_ptr(t_mlx_vars *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->player_right);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->player_left);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->goal);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->wall);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->item1);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->item2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->empty1);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->empty2);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->empty3);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->empty4);
	return (0);
}

int	mlx_destroys(t_mlx_vars *mlx)
{
	destroy_img_ptr(mlx);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	return (0);
}

int	close_window(t_mlx_vars *mlx)
{
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}
