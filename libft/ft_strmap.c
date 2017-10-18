/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:11:06 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/28 13:35:42 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	int		i;

	i = 0;
	if (s && f)
	{
		res = (char *)malloc(ft_strlen(s) + 1);
		if (res == NULL)
			return (NULL);
		while (*s)
			res[i++] = (f)(*s++);
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
