# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 22:04:29 by takira            #+#    #+#              #
#    Updated: 2022/11/26 19:58:34 by takira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

ifdef WITH_TEST
	CFLAGS		+= -g -fsanitize=address -fsanitize=undefined
endif


# MONDATORY
NAME			= so_long

INCLUDE_DIR		= ./includes
HEADERS			= so_long.h

LIBFT_DIR		= ./lib/libft
LIBFT			= libft

LIBFTPRINTF_DIR	= ./lib/libftprintf
LIBFTPRINTF		= libftprintf

LIBGNL_DIR		= ./lib/gnl
LIBGNL			= libgnl

MLX_DIR			= ./minilibx-linux
X11_DIR			= /usr/X11

INCLUDES		= -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(LIBFTPRINTF_DIR) -I $(LIBGNL_DIR) -I $(MLX_DIR) -I $(X11_DIR)/include
LIBS_DIR 		= -L $(LIBFT_DIR) -L $(LIBFTPRINTF_DIR) -L $(LIBGNL_DIR) -L $(MLX_DIR) -L $(X11_DIR)/lib -L $(X11_DIR)
LIBS 			= -lft -lftprintf -lgnl -lmlx -lX11 -lXext

VPATH			= $(SRC_DIR):$(INCLUDE_DIR):$(BONUS_SRC_DIR):$(BONUS_INCLUDE_DIR)
SRC_DIR			= ./srcs
SRCS			= main.c \
				  read_and_create_map.c \
				  valid_map.c \
				  bfs.c \
				  create_grid_for_bfs.c \
				  create_game_screen.c \
				  sl_utils.c \
				  mlx_utils.c \
				  mlx_keyhooks.c \
				  get_map_img.c \

# BONUS
BONUS_NAME		= so_long_bonus

BONUS_INCLUDES	= -I $(BONUS_INCLUDE_DIR) -I $(LIBFT_DIR) -I $(LIBFTPRINTF_DIR) -I $(LIBGNL_DIR) -I $(MLX_DIR) -I $(X11_DIR)/include

OBJ_DIR			= ./objs
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

BONUS_INCLUDE_DIR	= ./bonus/includes
BONUS_HEADERS		= so_long_bonus.h

BONUS_SRC_DIR	= ./bonus
BONUS_SRCS		= main_bonus.c \
				  read_and_create_map_bonus.c \
				  valid_map_bonus.c \
				  bfs_bonus.c \
				  create_grid_for_bfs_bonus.c \
				  create_game_screen_bonus.c \
				  sl_utils_bonus.c \
				  mlx_utils_bonus.c \
				  mlx_hooks_bonus.c \
				  mlx_animation_bonus.c \
				  get_map_img_bonus.c \

BONUS_OBJ_DIR	= ./bonus/objs
BONUS_OBJS		= $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRCS:%.c=%.o))


# OS Check
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= -L /usr/X11R6/lib
	LIBS 		+= -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LIBS 		+= -lmlx_Linux
endif


# RULES
all:		$(NAME)

$(NAME):	$(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFTPRINTF_DIR)
	@make -C $(LIBGNL_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBFTPRINTF_DIR)
	@make clean -C $(LIBGNL_DIR)
	@make clean -C $(MLX_DIR)

fclean:		clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBFTPRINTF_DIR)
	@make fclean -C $(LIBGNL_DIR)

re:			fclean all

bonus:	$(BONUS_NAME)

$(BONUS_NAME):	$(BONUS_OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFTPRINTF_DIR)
	@make -C $(LIBGNL_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(BONUS_INCLUDE) -c $< -o $@

bonus_clean:
	rm -rf $(BONUS_OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBFTPRINTF_DIR)
	@make clean -C $(LIBGNL_DIR)
	@make clean -C $(MLX_DIR)

bonus_fclean:	bonus_clean
	rm -f $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBFTPRINTF_DIR)
	@make fclean -C $(LIBGNL_DIR)

test:
	make all WITH_TEST=1

test_bonus:
	make bonus WITH_TEST=1

norm:
	@norminette --version
	norminette $(SRC_DIR) $(INCLUDE_DIR) $(BONUS_SRC_DIR)


.PHONY:		all clean fclean re bonus bonus_clean bonus_fclean norm test test_bonus
