/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:06:18 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:46:47 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	minsize(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cpy_len;
	size_t	start_idx;
	char	*ret_str;

	if (s == NULL)
		return (NULL);
	start_idx = (size_t)start;
	if (ft_strlen(s) < start_idx + 1)
		cpy_len = 0;
	else
		cpy_len = minsize(ft_strlen(s) - start_idx, len);
	ret_str = (char *)malloc(sizeof(char) * (cpy_len + 1));
	if (ret_str == NULL)
		return (NULL);
	ft_strlcpy(ret_str, &s[start_idx], cpy_len + 1);
	return (ret_str);
}
