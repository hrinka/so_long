/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:10:20 by takira            #+#    #+#             */
/*   Updated: 2022/11/26 19:10:21 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include "./../minilibx-linux/mlx.h"
# include "./../lib/libft/libft.h"
# include "./../lib/libftprintf/ft_printf.h"
# include "./../lib/gnl/get_next_line.h"

# define KEY_ESC	0xff1b
# define KEY_LEFT	0xff51
# define KEY_UP		0xff52
# define KEY_RIGHT	0xff53
# define KEY_DOWN	0xff54

# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		33

# define MAP_WALL	'1'
# define MAP_EMPTY	'0'
# define MAP_ITEM	'C'
# define MAP_PLAYER	'P'
# define MAP_GOAL	'E'

# define PASS	1
# define FAIL	0

# define IMAGE_SIZE 30

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		next_x;
	int		next_y;
	int		cnt_step;
	int		cnt_item;
	bool	can_exit;
	bool	is_facing_right;
	bool	flg_get_item;
}			t_player;

typedef struct s_map_info
{
	char	**map_arr;
	char	chr_wall;
	char	chr_empty;
	char	chr_item;
	char	chr_player;
	char	chr_exit;
	int		cnt_item;
	int		cnt_start;
	int		cnt_exit;
	int		cnt_others;
	size_t	size_col;
	size_t	size_row;
	size_t	sx;
	size_t	sy;
}			t_map_info;

typedef struct s_map_img
{
	void	*player_right;
	void	*player_left;
	void	*goal;
	void	*wall;
	void	**empties;
	void	**items;
}			t_map_img;

typedef struct s_mlx_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player_ptr;
	t_map_info	*map_ptr;
	t_map_img	*img_ptr;
	bool		is_game_end;
}				t_mlx_vars;

// init
void	init_mlx_ptr(t_mlx_vars *mlx, t_map_info *m, \
t_map_img *i, t_player *p);
void	init_mapinfo(t_map_info *info);
void	init_map_img(t_mlx_vars mlx, t_map_img *img);

// read and create map
int		read_and_valid_maps(char *path, t_map_info *info);

// get img
void	*get_player_img(t_mlx_vars mlx);
void	*get_empty_img(t_mlx_vars mlx);
void	*get_item_img(t_mlx_vars mlx);
void	*get_img_ptr(t_mlx_vars *mlx, int row, int col);
int		valid_map_img(t_map_img *img);

// create game screen
void	move_pos_and_redraw(t_mlx_vars *mlx, t_map_info *map, t_player *player);
int		draw_game_screen(t_mlx_vars *mlx);
int		can_player_move(t_map_info map, t_player player);

// mlx keyhooks
void	mlx_hooks(t_mlx_vars *mlx);

// mlx utils
void	*file_to_img(t_mlx_vars mlx, char *filepath);
void	put_img(t_mlx_vars *mlx, void *img_ptr, int row, int col);
int		close_window(t_mlx_vars *mlx);
int		mlx_destroys(t_mlx_vars *mlx);
int		destroy_img_ptr(t_mlx_vars *mlx);

// sl utils
void	print_step_in_std(t_mlx_vars *mlx);
int		free_map_arr(t_map_info *info, int ret_val);
int		error_exit(char *msg);
int		get_map_kinds(void **arr);
size_t	ft_strlen_sl(const char *str);

#endif
