/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:26:14 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:26:14 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long_bonus.h"

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q so_long_bonus");
}

static int	init_map_img_b(t_mlx_vars mlx, t_img *img)
{
	img->player_right1 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_R1);
	img->player_right2 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_R2);
	img->player_right3 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_R3);
	img->player_right4 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_R4);
	img->player_right5 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_R5);
	img->player_left1 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_L1);
	img->player_left2 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_L2);
	img->player_left3 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_L3);
	img->player_left4 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_L4);
	img->player_left5 = xpm_to_img_ptr_b(mlx, IMG_PLAYER_L5);
	img->goal = xpm_to_img_ptr_b(mlx, IMG_GOAL);
	img->wall = xpm_to_img_ptr_b(mlx, IMG_WALL);
	img->item1 = xpm_to_img_ptr_b(mlx, IMG_ITEM_1);
	img->item2 = xpm_to_img_ptr_b(mlx, IMG_ITEM_2);
	img->item3 = xpm_to_img_ptr_b(mlx, IMG_ITEM_3);
	img->empty1 = xpm_to_img_ptr_b(mlx, IMG_EMPTY_1);
	img->empty2 = xpm_to_img_ptr_b(mlx, IMG_EMPTY_2);
	img->empty3 = xpm_to_img_ptr_b(mlx, IMG_EMPTY_3);
	img->empty4 = xpm_to_img_ptr_b(mlx, IMG_EMPTY_4);
	if (null_check_for_map_img_b(img) == FAIL)
		return (FAIL);
	return (PASS);
}

static void	init_player_b(t_player *player, t_map_param map)
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

static void	init_mlx_ptr_b(t_mlx_vars *x, t_map_param *m, t_img *i, t_player *p)
{
	const int	size_x = (int)m->size_x * IMAGE_SIZE;
	const int	size_y = (int)m->size_y * IMAGE_SIZE;

	x->mlx = mlx_init();
	if (!x->mlx)
		error_exit_b("[Fail] Fail to init minilibx.", NULL);
	x->win = mlx_new_window(x->mlx, size_x, size_y, "./so_long");
	if (!x->win)
		error_exit_b("[Fail] Fail to generate window.", NULL);
	x->map = m;
	x->img = i;
	x->player = p;
	if (init_map_img_b(*x, i) == FAIL)
		error_exit_b("[Fail] Fail to get map img.", NULL);
	init_player_b(p, *m);
	x->is_game_end = false;
	x->animation_cnt = 0;
	x->player_flame = 0;
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
		error_exit_b("[Invalid Arg] Cmd>$./so_long ./assets/map/<file>", NULL);
	filepath = valid_map_path_name_b(argv[1]);
	if (!filepath)
		error_exit_b("[Invalid File] only read *.ber", NULL);
	ft_printf("Read file: %s\n", filepath);
	read_and_valid_map_b(filepath, &map);
	init_mlx_ptr_b(&mlx, &map, &img, &player);
	if (draw_game_screen_b(&mlx) == FAIL)
		error_exit_b("Can't find img_ptr.", &mlx);
	ft_printf("[GAME START] There are %d items !!\n", map.cnt_item);
	mlx_hooks_b(&mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx_and_map_b(&mlx);
	free(filepath);
	return (0);
}
