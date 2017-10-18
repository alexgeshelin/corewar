/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:41:44 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/28 13:57:46 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	if (s && f)
	{
		res = (char *)malloc(ft_strlen(s) + 1);
		if (res == NULL)
			return (NULL);
		while (*s)
		{
			res[i] = (f)(i, *s++);
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
