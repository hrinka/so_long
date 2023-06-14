/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:06:09 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/15 01:06:09 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret_ptr;
	size_t	i;
	size_t	len;

	ret_ptr = NULL;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			ret_ptr = (char *)&s[i];
		i++;
	}
	return (ret_ptr);
}
