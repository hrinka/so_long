/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:35:31 by takira            #+#    #+#             */
/*   Updated: 2022/11/28 15:35:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"

static void	init_player(t_player *player, t_map_info map)
{
	player->pos_x = (int)map.start_x;
	player->pos_y = (int)map.start_y;
	player->next_x = player->pos_x;
	player->next_y = player->pos_y;
	player->cnt_step = 0;
	player->cnt_item = 0;
	player->can_exit = false;
	player->is_facing_right = true;
}

void	init_mlx_ptr(t_mlx_vars *mlx, t_map_info *m, t_map_img *i, t_player *p)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
	(int)m->size_row * IMAGE_SIZE, \
	(int)m->size_col * IMAGE_SIZE, \
	"so_long");
	mlx->map_ptr = m;
	mlx->img_ptr = i;
	mlx->player_ptr = p;
	init_map_img(*mlx, i);
	init_player(p, *m);
	mlx->is_game_end = false;
}

void	init_mapinfo(t_map_info *info)
{
	info->map_arr = NULL;
	info->cnt_item = 0;
	info->cnt_start = 0;
	info->cnt_exit = 0;
	info->cnt_others = 0;
	info->size_col = 0;
	info->size_row = 0;
}

void	init_map_img(t_mlx_vars mlx, t_map_img *img)
{
	img->player_right = xpm_to_img_ptr(mlx, "./assets/img/cow_r1.xpm");
	img->player_left = xpm_to_img_ptr(mlx, "./assets/img/cow_l1.xpm");
	img->goal = xpm_to_img_ptr(mlx, "./assets/img/goal.xpm");
	img->wall = xpm_to_img_ptr(mlx, "./assets/img/wall.xpm");
	img->item1 = xpm_to_img_ptr(mlx, "./assets/img/item1.xpm");
	img->item2 = xpm_to_img_ptr(mlx, "./assets/img/item2.xpm");
	img->empty1 = xpm_to_img_ptr(mlx, "./assets/img/grass1.xpm");
	img->empty2 = xpm_to_img_ptr(mlx, "./assets/img/grass2.xpm");
	img->empty3 = xpm_to_img_ptr(mlx, "./assets/img/grass3.xpm");
	img->empty4 = xpm_to_img_ptr(mlx, "./assets/img/grass4.xpm");
	if (null_check_for_map_img(img) == FAIL)
		error_exit("Img_ptr is NULL");
}
