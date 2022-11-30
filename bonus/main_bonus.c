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

static void	init_t_player_b(t_player *player, t_map_param map)
{
	player->pos_x = map.start_x;
	player->pos_y = map.start_y;
	player->next_x = (int)player->pos_x;
	player->next_y = (int)player->pos_y;
	player->cnt_step = 0;
	player->cnt_item = 0;
	player->can_exit = false;
	player->is_player_facing_r = true;
	player->flg_get_item = false;
}

static void	set_enem_param(t_player *player, int i, int j, int k)
{
	player->enemy[k].pos_y = i;
	player->enemy[k].pos_x = j;
	player->enemy[k].ny = j;
	player->enemy[k].nx = i;
	player->enemy[k].anime_flame = 0;
	player->enemy[k].is_enemy_facing_r = true;
}

static int	get_enemy_coordinate(t_player *player, t_map_param *map)
{
	int	i;
	int	j;
	int	k;

	player->enemy = (t_enemy *)ft_calloc(sizeof(t_enemy), map->cnt_enemy + 1);
	if (!player->enemy)
		return (FAIL);
	i = 0;
	k = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map_arr[i][j] == CHR_ENEMY)
			{
				set_enem_param(player, i, j, k);
				k++;
			}
			j++;
		}
		i++;
	}
	return (PASS);
}

static void	init_mlx_ptr_b(t_mlx_vars *x, t_map_param *m, t_img *i, t_player *p)
{
	const int	size_x = (int)m->size_x * IMAGE_SIZE;
	const int	size_y = (int)m->size_y * IMAGE_SIZE + Y_OFFSET;

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
	init_t_player_b(p, *m);
	x->is_game_end = false;
	x->player_anime_flame = 0;
	x->enemy_anime_flame = 0;
	x->player_flame = 0;
	x->enemy_move_flame = 0;
	x->enemy_move_flame = 0;
	x->enemy_anime_no = 0;
	x->enemy_move_no = 0;
	if (get_enemy_coordinate(p, m) == FAIL)
		error_exit_b("[Fail] Fail to get enemy's info.", NULL);
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
	print_map_b(*mlx.map, "main");
	mlx_hooks_b(&mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx_and_map_b(&mlx);
	free(filepath);
	return (0);
}
