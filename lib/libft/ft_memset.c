/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:05:15 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:46:24 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*str;
	const unsigned char	chr = (const unsigned char)c;
	size_t				i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = chr;
	return (s);
}
