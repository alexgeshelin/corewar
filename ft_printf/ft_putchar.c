/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:16:37 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/29 14:17:09 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_p(char c)
{
	write(1, &c, 1);
	g_count++;
}

void	ft_putwchar(wchar_t wint)
{
	char *str;

	str = malloc(5 * sizeof(char));
	if (wint <= 0x7F)
	{
		str[0] = (char)wint;
		if (wint == 0)
			ft_putchar_p(0);
		str[1] = '\0';
	}
	else if (wint <= 0x7FF)
	{
		str[0] = (char)(((wint & 0x07c0) >> 6) + 0xc0);
		str[1] = (char)((wint & 0x003F) + 0x80);
		str[2] = '\0';
	}
	else if (wint <= 0xFFFF)
		ft_putwchar2(wint, str);
	ft_putstr_p(str);
	free(str);
}

void	ft_putwchar2(wchar_t wint, char *str)
{
	if (wint <= 0xFFFF)
	{
		str[0] = (char)(((wint & 0xF000) >> 12) + 0xE0);
		str[1] = (char)(((wint & 0x0Fc0) >> 6) + 0x80);
		str[2] = (char)((wint & 0x003F) + 0x80);
		str[3] = '\0';
	}
	else if (wint <= 0x10FFFF)
	{
		str[0] = (char)(((wint & 0x1c0000) >> 18) + 0xF0);
		str[1] = (char)(((wint & 0x03F000) >> 12) + 0x80);
		str[2] = (char)(((wint & 0x0Fc0) >> 6) + 0x80);
		str[3] = (char)((wint & 0x003F) + 0x80);
		str[4] = '\0';
	}
}

int		w_length(wint_t wint)
{
	if (wint <= 0x7F)
		return (1);
	else if (wint <= 0x7FF)
		return (2);
	else if (wint <= 0xFFFF)
		return (3);
	else if (wint <= 0x10FFFF)
		return (4);
	return (-1);
}
