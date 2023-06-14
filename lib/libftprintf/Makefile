CC			= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= libftprintf.a

SRCS		= printf_utils.c\
			ft_put_for_printf.c\
			ft_printf.c\
			compare_size.c\
			input_printf_format.c\
			vaild_info_for_each_fmt.c\
			print_num.c\
			print_string.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus:		all

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
