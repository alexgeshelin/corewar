/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:31:33 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/06 14:00:40 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nedded_size(int n)
{
	int size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char			*s;
	int				size;
	unsigned int	un;

	un = n;
	size = ft_nedded_size(n);
	if ((s = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		un = n * -1;
	}
	s[size--] = '\0';
	while (un)
	{
		s[size--] = un % 10 + '0';
		un = un / 10;
	}
	return (s);
}
