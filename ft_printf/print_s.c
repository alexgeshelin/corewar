/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 11:56:19 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/01 11:57:13 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_s(t_printf *mod, va_list vl)
{
	char	*s;
	wchar_t *w;

	if (!mod->l)
	{
		s = va_arg(vl, char *);
		if (!s)
			s = "(null)";
		if (!mod->minus)
			print_right_s(mod, s);
		else
			print_left_s(mod, s);
	}
	else
	{
		w = va_arg(vl, wchar_t *);
		if (w)
			print_ls(mod, w);
		else
			print_right_s(mod, "(null)");
	}
}

void			print_right_s(t_printf *mod, const char *s)
{
	int to_out;

	to_out = ft_strlen_p(s) < mod->precision ? ft_strlen_p(s) : mod->precision;
	if (mod->precision == -1)
		to_out = ft_strlen_p(s);
	if (mod->width != -1)
	{
		while (mod->width - to_out > 0)
		{
			mod->width--;
			mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
		}
	}
	while (to_out--)
		ft_putchar_p(*s++);
}

void			print_left_s(t_printf *mod, const char *s)
{
	int to_out;
	int outputed;

	outputed = 0;
	if (mod->precision != -1)
		to_out = ft_strlen_p(s) > mod->precision ? \
		mod->precision : ft_strlen_p(s);
	else
		to_out = ft_strlen_p(s);
	while (to_out--)
		ft_putchar_p(s[outputed++]);
	if (mod->width != -1)
	{
		mod->width -= outputed;
		while (mod->width > 0)
		{
			ft_putchar_p(' ');
			mod->width--;
		}
	}
}

static void		ls_h(t_printf *mod, int outed_bytes, wchar_t *wc)
{
	outed_bytes += w_length(*wc);
	while (mod->precision >= outed_bytes)
	{
		ft_putwchar(*wc++);
		outed_bytes += w_length(*wc);
	}
}

void			print_ls(t_printf *mod, wchar_t *wc)
{
	int bytes_to_out;
	int outed_bytes;
	int i;

	i = 0;
	outed_bytes = 0;
	bytes_to_out = 0;
	while (mod->precision >= bytes_to_out + w_length(wc[i]) && wc[i])
		bytes_to_out += w_length(wc[i++]);
	if (mod->precision == -1)
		bytes_to_out = wcharsize(wc);
	if (mod->width != -1)
	{
		while (mod->width > bytes_to_out)
		{
			mod->width--;
			mod->zero ? ft_putchar_p('0') : ft_putchar_p(' ');
		}
	}
	if (mod->precision == -1 || (mod->precision > wcharsize(wc)))
		while (*wc)
			ft_putwchar(*wc++);
	else
		ls_h(mod, outed_bytes, wc);
}
