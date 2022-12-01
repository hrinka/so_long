/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:04:17 by takira            #+#    #+#             */
/*   Updated: 2022/11/21 22:04:19 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/so_long.h"
/*
__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q so_long");
}
*/
static int	init_map_img(t_mlx_vars mlx, t_img *img)
{
	img->player_right = xpm_to_img_ptr(mlx, IMG_PLAYER_R);
	img->player_left = xpm_to_img_ptr(mlx, IMG_PLAYER_L);
	img->goal = xpm_to_img_ptr(mlx, IMG_GOAL);
	img->wall = xpm_to_img_ptr(mlx, IMG_WALL);
	img->item = xpm_to_img_ptr(mlx, IMG_ITEM);
	img->empty = xpm_to_img_ptr(mlx, IMG_EMPTY);
	if (null_check_for_map_img(img) == FAIL)
		return (FAIL);
	return (PASS);
}

static void	init_player(t_player *player, t_map_param map)
{
	player->pos_x = map.start_x;
	player->pos_y = map.start_y;
	player->next_x = (int)player->pos_x;
	player->next_y = (int)player->pos_y;
	player->cnt_step = 0;
	player->cnt_item = 0;
	player->can_exit = false;
	player->is_facing_right = true;
	player->flg_get_item = false;
}

static void	init_mlx_ptr(t_mlx_vars *mlx, t_map_param *m, t_img *i, t_player *p)
{
	const int	size_x = (int)m->size_x * IMAGE_SIZE;
	const int	size_y = (int)m->size_y * IMAGE_SIZE;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		err_exit("[Fail] Fail to init minilibx.", NULL);
	mlx->win = mlx_new_window(mlx->mlx, size_x, size_y, "./so_long");
	if (!mlx->win)
		err_exit("[Fail] Fail to generate window.", NULL);
	mlx->map = m;
	mlx->img = i;
	if (init_map_img(*mlx, i) == FAIL)
		err_exit("[Fail] Fail to get map img.", mlx);
	mlx->player = p;
	init_player(p, *m);
	mlx->is_game_end = false;
}

int	main(int argc, char *argv[])
{
	t_mlx_vars	mlx;
	t_map_param	map;
	t_img		img;
	t_player	player;
	char		*filepath;

	errno = 0;
	if (argc != 2)
		err_exit("[Invalid Arg] Cmd>$./so_long ./assets/map/<file>", NULL);
	filepath = valid_map_path_name(argv[1]);
	if (!filepath)
		err_exit("[Invalid File] only read *.ber", NULL);
	ft_printf("Read file: %s\n", filepath);
	read_and_valid_map(filepath, &map);
	init_mlx_ptr(&mlx, &map, &img, &player);
	if (draw_game_screen(&mlx) == FAIL)
		err_exit("Can't find img_ptr.", &mlx);
	ft_printf("[GAME START] There are %d items !!\n", map.cnt_item);
	mlx_key_hooks(&mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx_and_map(&mlx);
	return (0);
}
