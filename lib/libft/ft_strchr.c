/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:05:20 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:46:26 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	size_t	i;
	size_t	len;

	chr = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == chr)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}
