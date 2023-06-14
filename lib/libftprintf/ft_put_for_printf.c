/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_for_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:07:20 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:07:20 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf.h"

ssize_t	ft_putchar_for_printf(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t	ft_putstr_for_printf(char *s, int fd)
{
	ssize_t	put_bytes;

	put_bytes = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		put_bytes += ft_putchar_for_printf(*s++, fd);
		if (errno != 0)
			return (-1);
		if (put_bytes > INT_MAX)
			return (-1);
	}
	return (put_bytes);
}
