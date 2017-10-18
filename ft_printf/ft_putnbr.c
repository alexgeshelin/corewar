/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:09:32 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/30 12:12:58 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_p(long long int nb, int base, char *s)
{
	unsigned long long int unb;

	unb = (unsigned long long int)nb;
	if (nb < 0)
		unb = nb * -1;
	if (unb > (unsigned long long)(base - 1))
		ft_putnbr_p(unb / base, base, s);
	ft_putchar_p(s[unb % base]);
}

int		nbr_length_base(long long int nbr, int base)
{
	int						length;
	unsigned long long int	ui;

	length = 0;
	if (nbr == 0)
		return (1);
	ui = (unsigned long long)nbr;
	if (nbr < 0)
		ui = (unsigned long long)(nbr * -1);
	while (ui)
	{
		length++;
		ui /= base;
	}
	return (length);
}

void	ft_putunbr(unsigned long long int unb, int base, char *s)
{
	if (unb > (unsigned long long)(base - 1))
		ft_putunbr(unb / base, base, s);
	ft_putchar_p(s[unb % base]);
}

int		unbr_length(unsigned long long int unbr, int base, t_printf *mod)
{
	int length;

	length = 0;
	if (mod->type == 'o' && mod->sharp)
		length++;
	if (mod->type == 'p')
		length += 2;
	if ((mod->type == 'x' || mod->type == 'X') && mod->sharp)
		length += 2;
	if (unbr == 0)
		return (++length);
	while (unbr)
	{
		length++;
		unbr /= base;
	}
	return (length);
}
