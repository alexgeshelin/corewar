/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:30:30 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/28 16:36:14 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int i, size_t len)
{
	char	*new;
	int		j;

	j = 0;
	if (s == NULL)
		return (NULL);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	while (*s && len--)
	{
		new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}
