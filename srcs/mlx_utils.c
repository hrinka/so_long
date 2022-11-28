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

void	*file_to_img(t_mlx_vars mlx, char *filepath)
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
	size_t	i;

	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->player_right);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->player_left);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->goal);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->wall);
	i = 0;
	while (mlx->img_ptr->empties[i])
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->empties[i++]);
	free(mlx->img_ptr->empties);
	i = 0;
	while (mlx->img_ptr->items[i])
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr->items[i++]);
	free(mlx->img_ptr->items);
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
