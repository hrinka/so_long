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

NAME	= so_long

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

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

VPATH			= $(SRC_DIR)
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

OBJ_DIR			= ./objs
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

#BONUS_SRC_DIR	= ./bonus
#BONUS_SRCS		=
#BONUS_OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= -L /usr/X11R6/lib
	LIBS 		+= -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LIBS 		+= -lmlx_Linux
endif

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
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBFTPRINTF_DIR)
	@make fclean -C $(LIBGNL_DIR)

re:			fclean all

norm:
	@norminette --version
	norminette $(SRC_DIR) $(INCLUDE_DIR)

.PHONY:		all clean fclean re
