/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:47:54 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/06 13:47:55 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long int	get_unsigned(t_printf *mod, va_list vl)
{
	unsigned long long int i;

	if (mod->j)
		i = va_arg(vl, uintmax_t);
	else if (mod->ll)
		i = va_arg(vl, unsigned long long int);
	else if (mod->l)
		i = va_arg(vl, unsigned long int);
	else if (mod->z)
		i = va_arg(vl, size_t);
	else if (mod->h)
		i = (unsigned short int)va_arg(vl, unsigned int);
	else if (mod->hh)
		i = (unsigned char)va_arg(vl, unsigned int);
	else
		i = va_arg(vl, unsigned int);
	return (i);
}

void					print_sf(t_printf *mod, unsigned long long int i)
{
	if (mod->type == 'p' && mod->sharp)
		ft_putstr_p("0x");
	if (mod->type == 'o' && mod->sharp && i != 0)
		ft_putchar_p('0');
	if (mod->type == 'x' && mod->sharp && i != 0)
		ft_putstr_p("0x");
	if (mod->type == 'X' && mod->sharp && i != 0)
		ft_putstr_p("0X");
}

void					print_unsigned(t_printf *mod, va_list vl, int base)
{
	unsigned long long i;

	if (mod->type == 'O')
	{
		mod->l = 1;
		mod->type = 'o';
	}
	if (mod->type == 'U')
	{
		mod->type = 'u';
		mod->l = 1;
	}
	i = get_unsigned(mod, vl);
	if (!mod->minus)
		print_u_right(mod, i, base);
	else
		print_u_left(mod, i, base);
}

void					parse_mod(t_printf *mod, const char *format)
{
	while (*format && *format != mod->type)
	{
		if (*format == 'l' && *(format - 1) == 'l')
			mod->ll = 1;
		else if (*format == 'l' && *(format - 1) != 'l' && *(format + 1) != 'l')
			mod->l = 1;
		else if (*format == 'h' && *(format - 1) == 'h')
			mod->hh = 1;
		else if (*format == 'h' && *(format - 1) != 'h' && *(format + 1) != 'h')
			mod->h = 1;
		else if (*format == 'j')
			mod->j = 1;
		else if (*format == 'z')
			mod->z = 1;
		else if (*format == 't')
			mod->t = 1;
		format++;
	}
}
