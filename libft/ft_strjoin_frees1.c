/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_frees1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:28:59 by nsimonov          #+#    #+#             */
/*   Updated: 2017/03/28 20:12:47 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_frees1(char *s1, char *s2)
{
	int		j;
	int		k;
	int		lens1;
	size_t	len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	k = 0;
	while (s1[k])
		str[j++] = s1[k++];
	k = 0;
	while (s2[k])
		str[lens1++] = s2[k++];
	str[lens1] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}
