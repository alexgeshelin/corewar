/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:59:08 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/06 10:59:12 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		vl;
	t_printf	*mod;

	g_count = 0;
	mod = (t_printf *)malloc(sizeof(t_printf));
	va_start(vl, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == '%')
		{
			ft_putchar_p('%');
			format += 2;
		}
		else if (*format == '%' && *(format + 1) != '%')
		{
			parse_all(mod, ++format, vl);
			print_all(mod, vl);
			go_next(&format, mod);
		}
		else
			ft_putchar_p(*format++);
	}
	free(mod);
	va_end(vl);
	return (g_count);
}

void	go_next(const char **format, t_printf *mod)
{
	while (**format != 's' && **format != 'S' && **format != 'p' && \
			**format != 'D' && **format != 'd' && **format != 'i' && \
			**format != 'o' && **format != 'O' && **format != 'u' && \
			**format != 'U' && **format != 'x' && **format != 'X' && \
			**format != 'c' && **format != 'C' && **format && \
			**format != 'n' && **format != '%' && **format != mod->type)
	{
		(*format)++;
	}
	if (**format)
		(*format)++;
}

void	clear_mod(t_printf *mod)
{
	ft_bzero_p((void *)mod, sizeof(*mod));
	mod->width = -1;
	mod->precision = -1;
	mod->type = '~';
}
