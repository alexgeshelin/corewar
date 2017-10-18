/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:31:53 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/23 17:39:50 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *d, const char *s)
{
	size_t	len;
	char	*tmp;

	tmp = d;
	len = ft_strlen(d);
	while (*s)
	{
		tmp[len++] = *s++;
	}
	tmp[len] = '\0';
	return (d);
}
