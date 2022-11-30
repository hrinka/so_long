/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:25:29 by takira            #+#    #+#             */
/*   Updated: 2022/11/29 17:25:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "./../../minilibx-linux/mlx.h"
# include "./../../lib/libft/libft.h"
# include "./../../lib/libftprintf/ft_printf.h"
# include "./../../lib/gnl/get_next_line.h"

# define IMG_PLAYER_R1	"./bonus/img/player/cow_r1.xpm"
# define IMG_PLAYER_R2	"./bonus/img/player/cow_r2.xpm"
# define IMG_PLAYER_R3	"./bonus/img/player/cow_r3.xpm"
# define IMG_PLAYER_R4	"./bonus/img/player/cow_r4.xpm"
# define IMG_PLAYER_R5	"./bonus/img/player/cow_r5.xpm"
# define IMG_PLAYER_L1	"./bonus/img/player/cow_l1.xpm"
# define IMG_PLAYER_L2	"./bonus/img/player/cow_l2.xpm"
# define IMG_PLAYER_L3	"./bonus/img/player/cow_l3.xpm"
# define IMG_PLAYER_L4	"./bonus/img/player/cow_l4.xpm"
# define IMG_PLAYER_L5	"./bonus/img/player/cow_l5.xpm"
# define IMG_GOAL		"./bonus/img/goal.xpm"
# define IMG_WALL		"./bonus/img/wall.xpm"
# define IMG_ITEM_1		"./bonus/img/item/item1.xpm"
# define IMG_ITEM_2		"./bonus/img/item/item2.xpm"
# define IMG_ITEM_3		"./bonus/img/item/item3.xpm"
# define IMG_EMPTY_1	"./bonus/img/empty/grass1.xpm"
# define IMG_EMPTY_2	"./bonus/img/empty/grass2.xpm"
# define IMG_EMPTY_3	"./bonus/img/empty/grass3.xpm"
# define IMG_EMPTY_4	"./bonus/img/empty/grass4.xpm"

# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		33

# define KEY_ESC	0xff1b
# define KEY_LEFT	0xff51
# define KEY_UP		0xff52
# define KEY_RIGHT	0xff53
# define KEY_DOWN	0xff54

# define CHR_WALL	'1'
# define CHR_EMPTY	'0'
# define CHR_ITEM	'C'
# define CHR_PLAYER	'P'
# define CHR_GOAL	'E'

# define PASS		1
# define FAIL		0

# define MAP_MIN	2
# define MAP_MAX	66

# define IMAGE_SIZE 30

# define SPACES		"\t\n\v\f\r "
# define EXTENSION	".ber"

typedef struct s_player
{
	size_t	pos_x;
	size_t	pos_y;
	int		next_x;
	int		next_y;
	size_t	cnt_step;
	size_t	cnt_item;
	bool	can_exit;
	bool	is_facing_right;
	bool	flg_get_item;
}			t_player;

typedef struct s_map_param
{
	char	**map_arr;
	size_t	cnt_item;
	size_t	cnt_start;
	size_t	cnt_exit;
	size_t	cnt_others;
	size_t	size_x;
	size_t	size_y;
	size_t	start_x;
	size_t	start_y;
}			t_map_param;

typedef struct s_img //TODO: 配列化, mandatory 簡略化
{
	void	*player_right1;
	void	*player_right2;
	void	*player_right3;
	void	*player_right4;
	void	*player_right5;
	void	*player_left1;
	void	*player_left2;
	void	*player_left3;
	void	*player_left4;
	void	*player_left5;
	void	*goal;
	void	*wall;
	void	*empty1;
	void	*empty2;
	void	*empty3;
	void	*empty4;
	void	*item1;
	void	*item2;
	void	*item3;
	void	*enemy_right1;
	void	*enemy_right2;
	void	*enemy_right3;
	void	*enemy_right4;
	void	*enemy_right5;
	void	*enemy_right6;
	void	*enemy_right7;
	void	*enemy_left1;
	void	*enemy_left2;
	void	*enemy_left3;
	void	*enemy_left4;
	void	*enemy_left5;
	void	*enemy_left6;
	void	*enemy_left7;
}			t_img;

typedef struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map_param	*map;
	t_img		*img;
	bool		is_game_end;
	int			animation_cnt;
	int			player_flame;
}				t_mlx_vars;

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

// read and create map
int		read_and_valid_map_b(char *path, t_map_param *map);

// map valid
int		valid_map_b(t_map_param *map);

// bfs
void	bfs_b(int **visited, t_map_param map);
//void	print_bfs_b(int **grid, int y, int x, char *str);
//void	print_map_b(t_map_param map, char *str);

// create grid for bfs
int		**create_visited_b(char **map_arr, size_t y, size_t x);
void	free_grid_b(int **grid, size_t y);

// get img
void	*get_player_img_b(t_mlx_vars mlx);
void	*get_empty_img_b(t_mlx_vars mlx, size_t y, size_t x);
void	*get_item_img_b(t_mlx_vars mlx, size_t y, size_t x);
void	*get_img_ptr_b(t_mlx_vars *mlx, size_t y, size_t x);
int		null_check_for_map_img_b(t_img *img);

// create game screen
int		draw_game_screen_b(t_mlx_vars *mlx);
void	move_and_judge_finish_b(t_mlx_vars *mlx, int dy, int dx);
int		check_to_can_move_next_pos_b(t_mlx_vars *mlx, int dy, int dx);

// mlx keyhooks
void	mlx_hooks_b(t_mlx_vars *mlx);

// mlx animation
int		run_animation_b(t_mlx_vars *mlx);

// mlx utils
void	*xpm_to_img_ptr_b(t_mlx_vars mlx, char *filepath);
void	put_img_b(t_mlx_vars *mlx, void *img, size_t y, size_t x);
int		close_window_b(t_mlx_vars *mlx);
int		destroy_mlx_and_map_b(t_mlx_vars *mlx);

// sl utils
void	print_step_to_stdout_b(t_mlx_vars *mlx);
int		free_map_arr_b(t_map_param *map, int ret_val);
int		error_exit_b(char *msg, t_mlx_vars *mlx);
char	*valid_map_path_name_b(char *argv);

#endif
