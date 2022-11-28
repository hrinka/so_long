# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 19:18:14 by takira            #+#    #+#              #
#    Updated: 2022/11/26 19:27:17 by takira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

SRCS		= ft_strlen.c \
				ft_strlcpy.c \
              	ft_strchr.c \
              	ft_substr.c \
              	ft_strtrim.c \

OBJS		= $(SRCS:.c=.o)


$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			rm -f $(OBJS) $(BONUSOBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
