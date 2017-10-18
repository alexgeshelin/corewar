/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:11:11 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/29 12:58:54 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		len--;
		s++;
	}
	if (len < 0)
		len = 0;
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	while (i < len)
		new[i++] = *s++;
	new[i] = '\0';
	return (new);
}
