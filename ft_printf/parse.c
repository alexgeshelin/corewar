/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 16:45:13 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/22 16:45:16 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_all(t_printf *mod, const char *f, va_list vl)
{
	int i;

	i = 0;
	clear_mod(mod);
	while (f[i] && (f[i] == 's' || f[i] == 'S' || f[i] == 'p' || \
			f[i] == 'D' || f[i] == 'd' || f[i] == 'i' || f[i] == '.' || \
			f[i] == 'o' || f[i] == 'O' || f[i] == 'u' || f[i] == ' ' || \
			f[i] == 'U' || f[i] == 'x' || f[i] == 'X' || f[i] == 'c' || \
			f[i] == 'C' || f[i] == '%' || f[i] == 'n' || f[i] == '*' || \
			f[i] == 'l' || f[i] == 'h' || f[i] == 'j' || f[i] == 'z' || \
			f[i] == 't' || (f[i] >= '0' && f[i] <= '9') || f[i] == '-' || \
			f[i] == '#' || f[i] == '+' || f[i] == '%' || f[i] == 'b'))
	{
		i++;
	}
	if (f[i])
		mod->type = f[i];
	parse_spec(mod, f);
	parse_flags(mod, f);
	parse_width(mod, f, vl);
	parse_precision(mod, f, vl);
	parse_mod(mod, f);
}

void	parse_spec(t_printf *mod, const char *format)
{
	while (*format && *format != mod->type)
	{
		if (*format == 's' || *format == 'S' || *format == 'p' || \
			*format == 'D' || *format == 'd' || *format == 'i' || \
			*format == 'o' || *format == 'O' || *format == 'u' || \
			*format == 'U' || *format == 'x' || *format == 'X' || \
			*format == 'c' || *format == 'C' || *format == '%' ||  \
			*format == 'n' || *format == 'b')
		{
			mod->type = *format;
			break ;
		}
		format++;
	}
}

void	parse_flags(t_printf *mod, const char *format)
{
	while (*format && *format != mod->type)
	{
		if (*format == '-')
			mod->minus = 1;
		if (*format == '+')
			mod->plus = 1;
		if (*format == '0')
			if (!ft_isdigit_p(*(format - 1)))
				mod->zero = 1;
		if (*format == '#')
			mod->sharp = 1;
		if (*format == ' ')
			mod->space = 1;
		format++;
	}
}

void	parse_precision(t_printf *mod, const char *format, va_list vl)
{
	int prec;

	while (*format && *format != mod->type)
	{
		if (*format == '.' && *(format + 1) != '*')
			mod->precision = ft_atoi_p(format + 1);
		else if (*format == '.' && *(format + 1) == '*')
		{
			prec = va_arg(vl, int);
			if (prec < 0 && mod->type != 'd')
				prec = prec * -1;
			mod->precision = prec;
		}
		format++;
	}
}

void	parse_width(t_printf *mod, const char *format, va_list vl)
{
	int width;

	while (*format && *format != mod->type)
	{
		if (*format == '.')
			break ;
		else if (*format >= '1' && *format <= '9' && \
				(*(format - 1) < '1' || *(format - 1) > '9'))
			mod->width = ft_atoi_p(format);
		else if (*format == '*')
		{
			width = va_arg(vl, int);
			if (width < 0)
			{
				width *= -1;
				mod->minus = 1;
			}
			mod->width = width;
		}
		format++;
	}
}
