/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:11:13 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/26 09:23:47 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lettercounter(char const *s, int i, char c)
{
	int j;

	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

int		ft_wordcounter(char const *s, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			n++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (n);
}

char	*ft_makeword(const char *s, int x, char c)
{
	int		i;
	int		let;
	char	*str;

	i = 0;
	let = ft_lettercounter(s, x, c);
	str = (char*)malloc(sizeof(char) * (let + 1));
	if (!str)
		return (NULL);
	while (i < let)
		str[i++] = s[x++];
	str[i] = '\0';
	return (str);
}

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		x;
	char	**ptr;

	i = 0;
	x = 0;
	if (s == NULL)
		return (0);
	ptr = (char**)malloc(sizeof(char*) * (ft_wordcounter(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[x] == c)
		x++;
	while (s[x] != '\0')
	{
		ptr[i] = ft_makeword(s, x, c);
		x = x + ft_lettercounter(s, x, c);
		i++;
		while (s[x] == c)
			x++;
	}
	ptr[i] = 0;
	return (ptr);
}
