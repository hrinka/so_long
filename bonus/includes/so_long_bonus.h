/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:03:40 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:03:41 by hrinka           ###   ########.fr       */
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

// map image
# define CNT_PLAYER_FLM	5
# define CNT_ITEM		3
# define CNT_EMPTY		4
# define CNT_ENEMY_FLM	7

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
# define IMG_ENEMY_R1	"./bonus/img/enemy/slime_r1.xpm"
# define IMG_ENEMY_R2	"./bonus/img/enemy/slime_r2.xpm"
# define IMG_ENEMY_R3	"./bonus/img/enemy/slime_r3.xpm"
# define IMG_ENEMY_R4	"./bonus/img/enemy/slime_r4.xpm"
# define IMG_ENEMY_R5	"./bonus/img/enemy/slime_r5.xpm"
# define IMG_ENEMY_R6	"./bonus/img/enemy/slime_r6.xpm"
# define IMG_ENEMY_R7	"./bonus/img/enemy/slime_r7.xpm"
# define IMG_ENEMY_L1	"./bonus/img/enemy/slime_l1.xpm"
# define IMG_ENEMY_L2	"./bonus/img/enemy/slime_l2.xpm"
# define IMG_ENEMY_L3	"./bonus/img/enemy/slime_l3.xpm"
# define IMG_ENEMY_L4	"./bonus/img/enemy/slime_l4.xpm"
# define IMG_ENEMY_L5	"./bonus/img/enemy/slime_l5.xpm"
# define IMG_ENEMY_L6	"./bonus/img/enemy/slime_l6.xpm"
# define IMG_ENEMY_L7	"./bonus/img/enemy/slime_l7.xpm"

// key event
# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		33

# define KEY_ESC	0xff1b
# define KEY_LEFT	0xff51
# define KEY_UP		0xff52
# define KEY_RIGHT	0xff53
# define KEY_DOWN	0xff54

# define SIZE_TOP_STR	15
# define X_TOP_MSG		5
# define Y_TOP_MSG		10
# define X_TOP_STEP		10
# define Y_TOP_STEP		25
# define X_TOP_END_MSG	5
# define Y_TOP_END_MSG	15
# define C_TOP_MSG		0xFFFFFF
# define C_TOP_STEP		0xFFFFFF
# define C_TOP_END_MSG	0xFFFF00
# define C_TOP_CLEAR	0x000000

// for map file
# define CHR_WALL	'1'
# define CHR_EMPTY	'0'
# define CHR_ITEM	'C'
# define CHR_PLAYER	'P'
# define CHR_GOAL	'E'
# define CHR_ENEMY	'X'

# define MAP_MIN	2
# define MAP_MAX	66
# define IMAGE_SIZE 30
# define Y_OFFSET	30

# define SPACES		"\t\n\v\f\r "

# define FILE_EXTENSION	".ber"

// for animation flame
# define FPS_PLAYER_ANIMATION	15000
# define FPS_ENEMY_ANIMATION	3000
# define FPS_ENEMY_MOVE			40000
# define FPS_END_MSG			200000

// for func
# define PASS	1
# define FAIL	0

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	int		nx;
	int		ny;
	int		anime_flame;
	bool	is_enemy_facing_r;
}			t_enemy;

typedef struct s_player
{
	size_t	pos_x;
	size_t	pos_y;
	int		next_x;
	int		next_y;
	size_t	cnt_step;
	size_t	cnt_item;
	bool	can_exit;
	bool	is_player_facing_r;
	bool	flg_get_item;
	t_enemy	*enemy;
}			t_player;

typedef struct s_map_param
{
	char	**map_arr;
	size_t	cnt_item;
	size_t	cnt_start;
	size_t	cnt_exit;
	size_t	cnt_enemy;
	size_t	cnt_others;
	size_t	size_x;
	size_t	size_y;
	size_t	start_x;
	size_t	start_y;
}			t_map_param;

typedef struct s_img
{
	void	*goal;
	void	*wall;
	void	**players;
	void	**enemies;
	void	**empties;
	void	**items;
}			t_img;

typedef struct s_mlx_vars
{
	void		*mlx;
	void		*win;
	t_player	*player;
	t_map_param	*map;
	t_img		*img;
	bool		is_game_end;
	bool		is_game_over;
	bool		is_print_end;
	size_t		player_anime_flame;
	size_t		enemy_anime_flame;
	size_t		enemy_move_flame;
	int			player_flame;
	int			enemy_anime_no;
	int			enemy_move_no;
}				t_mlx_vars;

typedef struct s_queue
{
	int				x;
	int				y;
	int				cnt;
	struct s_queue	*next;
}					t_queue;

typedef struct s_bfs
{
	int	x;
	int	y;
	int	cnt;
}		t_bfs;

// read and create map
int		read_and_valid_map_b(char *path, t_map_param *map);

// map valid
int		valid_map_b(t_map_param *map);

// bfs
void	bfs_b(int **bfs_grid, t_map_param map, int start_y, int start_x);

// create grid for bfs
int		**create_bfs_grid_b(char **map_arr, size_t y, size_t x, bool for_enemy);

// init mlx
void	init_mlx_ptr_b(t_mlx_vars *x, t_map_param *m, t_img *i, t_player *p);

// init map img
int		init_map_img_b(t_mlx_vars *mlx, t_img *img);

// get img
void	*get_player_img_b(t_mlx_vars mlx);
void	*get_enemy_img_b(t_mlx_vars mlx, size_t flame, bool right);
void	*get_empty_img_b(t_mlx_vars mlx, size_t y, size_t x);
void	*get_item_img_b(t_mlx_vars mlx, size_t y, size_t x);
void	*get_img_ptr_b(t_mlx_vars *mlx, size_t y, size_t x);
int		null_check_for_map_img_b(t_img *img);

// player move
void	player_move_and_check_fin(t_mlx_vars *mlx, int dy, int dx);
int		draw_game_screen_b(t_mlx_vars *mlx);
int		check_to_can_move_next_pos_b(t_mlx_vars *mlx, int dy, int dx);

// enemy move
int		enemy_move_and_check_fin(t_mlx_vars *mlx, t_map_param *map);

// mlx keyhooks
void	mlx_hooks_b(t_mlx_vars *mlx);

// mlx animation
int		animation_b(t_mlx_vars *mlx);

// draw top screen info
int		draw_top_screen_info(t_mlx_vars *mlx);

// mlx utils
void	*xpm_to_img_ptr_b(t_mlx_vars mlx, char *filepath);
void	put_img_b(t_mlx_vars *mlx, void *img, size_t y, size_t x);
int		print_std_msg_and_loop_end_b(t_mlx_vars *mlx);
int		destroy_mlx_and_map_b(t_mlx_vars *mlx);

// mlx destroy
void	destroy_img_ptr_b(t_mlx_vars *mlx);

// sl utils
void	print_step_to_stdout_b(t_mlx_vars *mlx);
char	*valid_map_path_name_b(char *argv);
char	*convert_u_to_base(unsigned long u, int base, int capitals);
//void	print_bfs_b(int **grid, t_map_param map, char *str);
//void	print_map_b(t_map_param map, char *str);

// exit
void	free_grid_b(int **grid, size_t y);
int		free_map_arr_b(t_map_param *map, int ret_val);
int		err_exit_b(char *msg, t_mlx_vars *mlx);
void	free_alloc_img_arr_b(t_img *img);

#endif
