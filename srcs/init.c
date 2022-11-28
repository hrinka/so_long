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
	player->pos_x = (int)map.sx;
	player->pos_y = (int)map.sy;
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
	info->chr_wall = MAP_WALL;
	info->chr_empty = MAP_EMPTY;
	info->chr_item = MAP_ITEM;
	info->chr_player = MAP_PLAYER;
	info->chr_exit = MAP_GOAL;
	info->cnt_item = 0;
	info->cnt_start = 0;
	info->cnt_exit = 0;
	info->cnt_others = 0;
	info->size_col = 0;
	info->size_row = 0;
}

void	init_map_img(t_mlx_vars mlx, t_map_img *img)
{
	img->player_right = file_to_img(mlx, "./assets/img/cow_r1.xpm");
	img->player_left = file_to_img(mlx, "./assets/img/cow_l1.xpm");
	img->goal = file_to_img(mlx, "./assets/img/goal.xpm");
	img->wall = file_to_img(mlx, "./assets/img/wall1.xpm");
	img->items = (void **)malloc(sizeof(void *) * 3);
	if (!img->items)
		error_exit("Fail to get item img_ptr");
	img->items[0] = file_to_img(mlx, "./assets/img/item1.xpm");
	img->items[1] = file_to_img(mlx, "./assets/img/item2.xpm");
	img->items[2] = NULL;
	img->empties = (void **)malloc(sizeof(void *) * 6);
	if (!img->empties)
		error_exit("Fail to get empty img_ptr");
	img->empties[0] = file_to_img(mlx, "./assets/img/grass1.xpm");
	img->empties[1] = file_to_img(mlx, "./assets/img/grass2.xpm");
	img->empties[2] = file_to_img(mlx, "./assets/img/grass3.xpm");
	img->empties[3] = file_to_img(mlx, "./assets/img/grass4.xpm");
	img->empties[4] = file_to_img(mlx, "./assets/img/grass5.xpm");
	img->empties[5] = NULL;
	if (valid_map_img(img) == FAIL)
		error_exit("Fail to get empty img_ptr");
}
