/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:13:28 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/30 15:19:00 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t n)
{
	size_t lit_size;

	lit_size = ft_strlen(lit);
	if (lit_size == 0)
		return ((char *)big);
	while (*big && n)
	{
		if (*big == lit[0])
			if (n >= lit_size && ft_strlen(big) >= lit_size)
				if (ft_strncmp(big, lit, lit_size) == 0)
					return ((char*)big);
		big++;
		n--;
	}
	return (NULL);
}
