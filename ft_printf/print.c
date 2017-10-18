/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:52:08 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/06 11:52:11 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_u(t_printf *mod, va_list vl)
{
	if (mod->type == 'd' || mod->type == 'i' || mod->type == 'D')
		print_d(mod, vl, 10);
	else if (mod->type == 'o' || mod->type == 'O')
		print_unsigned(mod, vl, 8);
	else if (mod->type == 'u' || mod->type == 'U')
		print_unsigned(mod, vl, 10);
	else if (mod->type == 'x' || mod->type == 'X')
		print_unsigned(mod, vl, 16);
	else if (mod->type == 'c' || mod->type == 'C')
		print_c(mod, vl);
	else if (mod->type == 'b')
		print_unsigned(mod, vl, 2);
	else
		print_another(mod);
}

void			print_all(t_printf *mod, va_list vl)
{
	int *p;

	if (mod->type == 's')
		print_s(mod, vl);
	else if (mod->type == 'S')
	{
		mod->type = 's';
		mod->l = 1;
		print_s(mod, vl);
	}
	else if (mod->type == 'p')
	{
		mod->sharp = 1;
		mod->l = 1;
		print_unsigned(mod, vl, 16);
	}
	else if (mod->type == 'n')
	{
		p = va_arg(vl, void *);
		*p = g_count;
	}
	else
		print_u(mod, vl);
}

void			print_another(t_printf *mod)
{
	if (mod->type != '~')
	{
		if (mod->minus)
		{
			ft_putchar_p(mod->type);
			while (--mod->width > 0)
				ft_putchar_p(' ');
		}
		else
		{
			while (--mod->width > 0)
				mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
			ft_putchar_p(mod->type);
		}
	}
}

static void		print_lc(t_printf *mod, va_list vl)
{
	wchar_t wint;

	wint = va_arg(vl, unsigned int);
	if (mod->minus)
	{
		ft_putwchar(wint);
		mod->width -= w_length(wint);
		while (mod->width-- > 0)
			ft_putchar_p(' ');
	}
	else
	{
		mod->width -= w_length(wint);
		while (mod->width-- > 0)
			mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
		ft_putwchar(wint);
	}
}

void			print_c(t_printf *mod, va_list vl)
{
	if (mod->type != 'C' && mod->l == 0)
	{
		if (mod->minus)
		{
			ft_putchar_p((unsigned char)va_arg(vl, int));
			while (--mod->width > 0)
				ft_putchar_p(' ');
		}
		else
		{
			while (--mod->width > 0)
				mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
			ft_putchar_p((unsigned char)va_arg(vl, int));
		}
	}
	if (mod->type == 'C' || mod->l)
		print_lc(mod, vl);
}
