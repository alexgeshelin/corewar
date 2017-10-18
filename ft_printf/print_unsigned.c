/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:00:44 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/06 14:28:34 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		u_r2_helper(t_printf *mod, unsigned long long i, int base)
{
	if (i == 0)
		ft_putchar_p('0');
	else if (mod->type == 'X')
		ft_putunbr(i, base, "0123456789ABCEDF");
	else
		ft_putunbr(i, base, "0123456789abcdef");
}

void			print_u_r1(t_printf *mod, unsigned long long int i, int base)
{
	int to_out;

	to_out = mod->precision;
	if (to_out < unbr_length(i, base, mod))
		to_out = unbr_length(i, base, mod);
	while (mod->width - to_out > 0)
	{
		mod->width--;
		ft_putchar_p(' ');
	}
	to_out = unbr_length(i, base, mod);
	if (mod->type == 'p' || ((mod->type == 'x' || mod->type == 'X') \
		&& mod->sharp))
	{
		print_sf(mod, i);
		to_out -= 2;
	}
	while ((to_out < mod->precision) && mod->precision--)
		ft_putchar_p('0');
	if (mod->type == 'p' || mod->type == 'x' || mod->type == 'X')
		u_r2_helper(mod, i, base);
}

void			print_u_r2(t_printf *mod, unsigned long long int i, int base)
{
	int to_out;

	to_out = unbr_length(i, base, mod);
	if ((mod->type == 'X' || mod->type == 'x' || mod->type == 'p') \
		&& mod->sharp && mod->zero && mod->width > to_out)
	{
		print_sf(mod, i);
		mod->sharp = 0;
	}
	if (mod->type == 'o' && i == 0)
		to_out--;
	if ((mod->type == 'x' || mod->type == 'X') && i == 0)
		to_out -= 2;
	while (mod->width - to_out > 0)
	{
		mod->width--;
		mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
	}
}

void			print_u_right(t_printf *mod, unsigned long long int i, int base)
{
	if (mod->precision == 0 && i == 0 && !mod->sharp)
	{
		while (mod->width-- > 0)
			ft_putchar_p(' ');
		return ;
	}
	else if (mod->precision == 0 && i == 0 && mod->sharp && \
					(mod->type == 'x' || mod->type == 'X'))
		return ;
	else if (mod->precision > 0)
		print_u_r1(mod, i, base);
	else
		print_u_r2(mod, i, base);
	if ((mod->type == 'p' || mod->type == 'x' || mod->type == 'X') \
		&& mod->precision > 0)
		return ;
	print_sf(mod, i);
	if (mod->type == 'p' && i == 0 && mod->precision == 0)
		return ;
	mod->type == 'X' && i != 0 ? ft_putunbr(i, base, "0123456789ABCDEF") : \
	ft_putunbr(i, base, "0123456789abcdef");
}

void			print_u_left(t_printf *mod, unsigned long long int i, int base)
{
	int printed;

	printed = 0;
	while (mod->precision - unbr_length(i, base, mod) > 0)
	{
		mod->precision--;
		ft_putchar_p('0');
		printed++;
	}
	print_sf(mod, i);
	if (mod->type == 'X')
		ft_putunbr(i, base, "0123456789ABCDEF");
	else
		ft_putunbr(i, base, "0123456789abcdef");
	printed += unbr_length(i, base, mod);
	while (mod->width - printed > 0)
	{
		mod->width--;
		ft_putchar_p(' ');
	}
}
