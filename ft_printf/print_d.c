/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:53:59 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/27 18:54:02 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_d(t_printf *mod, va_list vl, int base)
{
	long long int i;

	if (mod->type == 'D')
	{
		mod->type = 'd';
		mod->l = 1;
	}
	i = get_long(mod, vl);
	if (!mod->minus)
		print_d_right(mod, i, base);
	else
		print_d_left(mod, i, base);
}

long long int	get_long(t_printf *mod, va_list vl)
{
	long long int i;

	if (mod->j)
		i = va_arg(vl, intmax_t);
	else if (mod->ll)
		i = va_arg(vl, long long int);
	else if (mod->l)
		i = va_arg(vl, long int);
	else if (mod->z)
		i = va_arg(vl, size_t);
	else if (mod->h)
		i = (short int)va_arg(vl, int);
	else if (mod->hh)
		i = (char)va_arg(vl, int);
	else
		i = va_arg(vl, int);
	return (i);
}

void			print_sign(t_printf *mod, long long int i, int *to_out)
{
	if (mod->plus)
	{
		i >= 0 ? ft_putchar_p('+') : ft_putchar_p('-');
		(*to_out)++;
	}
	else if (mod->space && i >= 0)
	{
		ft_putchar_p(' ');
		(*to_out)++;
	}
	else
	{
		if (i < 0)
		{
			ft_putchar_p('-');
			(*to_out)++;
		}
	}
}

void			print_d_right(t_printf *mod, long long int i, int base)
{
	if (mod->precision == 0 && i == 0)
	{
		while (mod->width > 0)
		{
			ft_putchar_p(' ');
			mod->width--;
		}
		return ;
	}
	else if (mod->precision >= 0)
		print_d_right1(mod, i, base);
	else
		print_d_right2(mod, i, base);
	ft_putnbr_p(i, base, "0123456789");
}

void			print_d_left(t_printf *mod, long long int i, int base)
{
	int printed;

	printed = 0;
	print_sign(mod, i, &printed);
	while (mod->precision - nbr_length_base(i, base) > 0)
	{
		mod->precision--;
		ft_putchar_p('0');
		printed++;
	}
	ft_putnbr_p(i, base, "0123456789");
	printed += nbr_length_base(i, base);
	while (mod->width - printed > 0)
	{
		mod->width--;
		ft_putchar_p(' ');
	}
}
