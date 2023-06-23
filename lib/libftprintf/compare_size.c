/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 01:06:37 by hrinka            #+#    #+#             */
/*   Updated: 2023/06/23 15:46:56 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	maxsize(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

size_t	minsize(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}
