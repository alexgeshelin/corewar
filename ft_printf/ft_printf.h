/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:51:48 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/22 16:43:03 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>

int g_count;

typedef	struct			s_printf
{
	char	type;
	int		width;
	int		precision;
	int		plus;
	int		minus;
	int		zero;
	int		space;
	int		sharp;
	int		h;
	int		hh;
	int		l;
	int		ll;
	int		j;
	int		z;
	int		t;
}						t_printf;

int						ft_printf(const char *format, ...);
void					parse_all(t_printf *mod, const char *f, va_list vl);
void					parse_spec(t_printf *mod, const char *format);
void					parse_flags(t_printf *mod, const char *format);
void					parse_width(t_printf *mod, const char *f, va_list vl);
void					parse_precision(t_printf *m, const char *f, va_list vl);
void					parse_mod(t_printf *mod, const char *format);
void					print_all(t_printf *mod, va_list vl);
void					print_s(t_printf *mod, va_list vl);
void					print_right_s(t_printf *mod, const char *s);
void					print_left_s(t_printf *mod, const char *s);
void					print_ls(t_printf *mod, wchar_t *t);
void					print_d(t_printf *mod, va_list vl, int base);
void					go_next(const char **format, t_printf *mod);
void					ft_bzero_p(void *m, size_t size);
void					ft_putchar_p(char c);
void					ft_putstr_p(const char *s);
int						ft_strlen_p(const char *s);
void					clear_mod(t_printf *mod);
int						ft_atoi_p(const char *s);
int						ft_isdigit_p(int c);
void					ft_putwchar(wchar_t wc);
void					ft_putwchar2(wchar_t wc, char *s);
void					ft_putnbr_p(long long int i, int base, char *s);
void					ft_putunbr(unsigned long long unb, int b, char *s);
int						nbr_length_base(long long int i, int base);
int						unbr_length(unsigned long long n, int b, t_printf *m);
long long int			get_long(t_printf *mod, va_list vl);
void					print_sign(t_printf *mod, long long int i, int *to_out);
void					print_d_right(t_printf *mod, long long int i, int base);
void					print_d_left(t_printf *mod, long long int i, int base);
void					print_d_right1(t_printf *mod, long long i, int base);
void					print_d_right2(t_printf *mod, long long i, int base);
void					print_u_right(t_printf *m, unsigned long long i, int b);
void					print_u_left(t_printf *m, unsigned long long i, int b);
void					print_u_r1(t_printf *m, unsigned long long i, int b);
void					print_u_r2(t_printf *m, unsigned long long i, int b);
void					print_unsigned(t_printf *mod, va_list vl, int base);
unsigned long long		get_unsigned(t_printf *mod, va_list vl);
void					print_sf(t_printf *mod, unsigned long long int i);
void					print_c(t_printf *mod, va_list vl);
int						w_length(wint_t wint);
int						wcharsize(wchar_t *w);
void					print_another(t_printf *mod);
#endif
