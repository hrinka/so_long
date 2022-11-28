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
# include <string.h>
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

# define CHR_WALL	'1'
# define CHR_EMPTY	'0'
# define CHR_ITEM	'C'
# define CHR_PLAYER	'P'
# define CHR_GOAL	'E'

# define PASS	1
# define FAIL	0

# define IMAGE_SIZE 30

# define IS_SPACE "\t\n\v\f\r "

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		next_x;
	int		next_y;
	size_t	cnt_step;
	size_t	cnt_item;
	bool	can_exit;
	bool	is_facing_right;
	bool	flg_get_item;
}			t_player;

typedef struct s_map_info
{
	char	**map_arr;
	size_t	cnt_item;
	size_t	cnt_start;
	size_t	cnt_exit;
	size_t	cnt_others;
	size_t	size_col;
	size_t	size_row;
	size_t	start_x;
	size_t	start_y;
}			t_map_info;

typedef struct s_map_img
{
	void	*player_right;
	void	*player_left;
	void	*goal;
	void	*wall;
	void	*empty1;
	void	*empty2;
	void	*empty3;
	void	*empty4;
	void	*item1;
	void	*item2;
}			t_map_img;

typedef struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map_info	*map;
	t_map_img	*img;
	bool		is_game_end;
}				t_mlx_vars;

// init
void	init_mlx_ptr(t_mlx_vars *mlx, t_map_info *m, t_map_img *i, t_player *p);
void	init_mapinfo(t_map_info *map);
void	init_map_img(t_mlx_vars mlx, t_map_img *img);

// read and create map
int		read_and_valid_maps(char *path, t_map_info *map);

// get img
void	*get_player_img(t_mlx_vars mlx);
void	*get_empty_img(t_mlx_vars mlx, int row, int col);
void	*get_item_img(t_mlx_vars mlx, int row, int col);
void	*get_img_ptr(t_mlx_vars *mlx, int row, int col);
int		null_check_for_map_img(t_map_img *img);

// create game screen
int		draw_game_screen(t_mlx_vars *mlx);
void	move_and_judge_finish(t_mlx_vars *mlx, int dy, int dx);
int		check_to_can_move_next_pos(t_mlx_vars *mlx, int dy, int dx);

// mlx keyhooks
void	mlx_hooks(t_mlx_vars *mlx);

// mlx utils
void	*xpm_to_img_ptr(t_mlx_vars mlx, char *filepath);
void	put_img(t_mlx_vars *mlx, void *img, int row, int col);
int		close_window(t_mlx_vars *mlx);
int		mlx_destroys(t_mlx_vars *mlx);
int		destroy_img_ptr(t_mlx_vars *mlx);

// sl utils
void	print_step_or_finish_to_stdout(t_mlx_vars *mlx);
int		free_map_arr(t_map_info *map, int ret_val);
int		error_exit(char *msg);
size_t	ft_strlen_sl(const char *str);

#endif
