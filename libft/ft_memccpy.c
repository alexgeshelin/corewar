/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:37:07 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/22 14:55:17 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*s1;
	const unsigned char *s2;

	s1 = dst;
	s2 = src;
	while (n--)
	{
		if (*s2 == (unsigned char)c)
		{
			*s1++ = *s2;
			return (s1);
		}
		*s1++ = *s2++;
	}
	return (NULL);
}
