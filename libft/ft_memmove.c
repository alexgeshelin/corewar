/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:11:05 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/30 16:18:19 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int					i;
	unsigned char		*udst;
	const unsigned char	*usrc;

	udst = dst;
	usrc = src;
	i = 0;
	if (src < dst)
	{
		while (len--)
			*(udst + len) = *(usrc + len);
	}
	else
	{
		while (len--)
		{
			*(udst + i) = *(usrc + i);
			i++;
		}
	}
	return (dst);
}
