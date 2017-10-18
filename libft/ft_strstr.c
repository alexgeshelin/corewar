/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:17:29 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/24 17:09:05 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *lit)
{
	size_t	lit_size;
	char	*tmp;

	tmp = (char *)big;
	lit_size = ft_strlen(lit);
	if (lit_size == 0)
		return (tmp);
	while (*big)
	{
		if (*big == lit[0])
			tmp = (char *)big;
		if (ft_strncmp(tmp, lit, lit_size) == 0 && ft_strlen(tmp) >= lit_size)
			return (tmp);
		big++;
	}
	return (NULL);
}
