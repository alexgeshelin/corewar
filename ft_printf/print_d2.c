/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:21:40 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/27 19:21:43 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_d_right1(t_printf *mod, long long int i, int base)
{
	int to_out;

	mod->zero = 0;
	to_out = mod->precision;
	if (to_out < nbr_length_base(i, base))
		to_out = nbr_length_base(i, base);
	if (mod->plus || i < 0 || (mod->space && i > 0))
		to_out++;
	while (mod->width - to_out > 0)
	{
		mod->width--;
		ft_putchar_p(' ');
	}
	print_sign(mod, i, &to_out);
	to_out = nbr_length_base(i, base);
	while (mod->precision - to_out > 0)
	{
		ft_putchar_p('0');
		mod->precision--;
	}
}

void	print_d_right2(t_printf *mod, long long int i, int base)
{
	int flag;
	int to_out;

	flag = 1;
	to_out = nbr_length_base(i, base);
	if (mod->zero)
	{
		flag = 0;
		print_sign(mod, i, &to_out);
	}
	if (mod->plus || i < 0 || (mod->space && i > 0))
		if (flag)
			to_out++;
	while (mod->width - to_out > 0)
	{
		mod->width--;
		mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
	}
	if (flag)
		print_sign(mod, i, &to_out);
}
