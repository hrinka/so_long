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
/*
__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q so_long_bonus");
}
*/
int	main(int argc, char *argv[])
{
	t_mlx_vars	mlx;
	t_map_param	map;
	t_img		img;
	t_player	player;
	char		*filepath;

	errno = 0;
	if (argc != 2)
		err_exit_b("[Invalid Arg] Cmd>$./so_long ./bonus/map/<file>", NULL);
	filepath = valid_map_path_name_b(argv[1]);
	if (!filepath)
		err_exit_b("[Invalid File] only read *.ber", NULL);
	ft_printf("Read file: %s\n", filepath);
	read_and_valid_map_b(filepath, &map);
	init_mlx_ptr_b(&mlx, &map, &img, &player);
	if (draw_game_screen_b(&mlx) == FAIL)
		err_exit_b("Can't find img_ptr.", &mlx);
	ft_printf("[GAME START] There are %d items !!\n", map.cnt_item);
	mlx_hooks_b(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
