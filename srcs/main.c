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
int	main(int argc, char *argv[])
{
	t_mlx_vars	mlx;
	t_map_info	map;
	t_map_img	img;
	t_player	player;
	char		*filepath;

	errno = 0;
	if (argc != 2)
		return (error_exit("[Invalid Arg] Cmd>$./so_long ./assets/map/<file>"));
	filepath = ft_strtrim(argv[1], IS_SPACE);
	if (!filepath)
		return (error_exit("Fail to get file path"));
	ft_printf("Read file: %s\n", filepath);
	if (read_and_valid_maps(filepath, &map) == FAIL)
		return (error_exit("Invalid Map"));
	init_mlx_ptr(&mlx, &map, &img, &player);
	ft_printf("[GAME START] There are %d items\n", map.cnt_item);
	draw_game_screen(&mlx);
	mlx_hooks(&mlx);
	mlx_loop(mlx.mlx);
	mlx_destroys(&mlx);
	ft_printf("[Exit] Good Bye!\n");
	return (0);
}
