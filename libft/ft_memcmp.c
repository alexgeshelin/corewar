/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:31:19 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/23 13:41:21 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ss1;
	const unsigned char *ss2;

	ss1 = s1;
	ss2 = s2;
	while (n--)
	{
		if (*ss1 - *ss2 != 0)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
	}
	return (0);
}
