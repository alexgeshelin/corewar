/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_coding_byte.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:55:51 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/02 14:55:54 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned char	make_coding_byte3(int a, int b, int c)
{
	return ((a << 6) | (b << 4) | (c << 2));
}

unsigned char	make_coding_byte2(int a, int b)
{
	return ((a << 6) | (b << 4));
}

unsigned char	make_coding_byte1(int a)
{
	return ((a << 6));
}

unsigned char	get_coding_byte(t_line *line)
{
	if (g_op_tab[get_index(line->op)].args_nbr == 3)
	{
		return (make_coding_byte3(get_code(line->args[0]), \
		get_code(line->args[1]), get_code(line->args[2])));
	}
	else if (g_op_tab[get_index(line->op)].args_nbr == 2)
	{
		return (make_coding_byte2(get_code(line->args[0]), \
		get_code(line->args[1])));
	}
	else if (g_op_tab[get_index(line->op)].args_nbr == 1)
	{
		return (make_coding_byte1(get_code(line->args[0])));
	}
	return (0);
}
