/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:39:10 by vtymchen          #+#    #+#             */
/*   Updated: 2017/05/19 17:39:14 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_arg(t_asm *as, const char *s, int index, t_line *ln)
{
	if (get_code(s) == REG_CODE)
		as->byte_code[as->byte++] = (unsigned char)ft_atoi(s + 1);
	else if (get_code(s) == IND_CODE)
		write_indir(as, s, ln);
	else if (get_code(s) == DIR_CODE && !ft_strchr(s, ':'))
		write_dir(as, s, index);
	else if (get_code(s) == DIR_CODE && ft_strchr(s, ':'))
		write_dir_l(as, s, index, ln);
}

void	write_indir(t_asm *as, const char *s, t_line *ln)
{
	unsigned char	*b;
	int				adrr;

	if (get_code(s) == IND_CODE && !ft_strchr(s, ':'))
	{
		adrr = ft_atoi(s);
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
	else if (get_code(s) == IND_CODE && ft_strchr(s, ':'))
	{
		adrr = get_pos(as, s + 1) - ln->pos;
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
}

void	write_dir_l(t_asm *as, const char *s, int index, t_line *ln)
{
	unsigned char	*b;
	int				adrr;

	if (get_code(s) == DIR_CODE && g_op_tab[index].flag && ft_strchr(s, ':'))
	{
		adrr = get_pos(as, s + 2) - ln->pos;
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
	else if (get_code(s) == DIR_CODE && !g_op_tab[index].flag && \
			ft_strchr(s, ':'))
	{
		adrr = get_pos(as, s + 2) - ln->pos;
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[3];
		as->byte_code[as->byte++] = b[2];
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
}

void	write_dir(t_asm *as, const char *s, int index)
{
	unsigned char	*b;
	int				adrr;

	if (get_code(s) == DIR_CODE && g_op_tab[index].flag && !ft_strchr(s, ':'))
	{
		adrr = ft_atoi(s + 1);
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
	else if (get_code(s) == DIR_CODE && !g_op_tab[index].flag && \
			!ft_strchr(s, ':'))
	{
		adrr = ft_atoi(s + 1);
		b = (unsigned char *)(&adrr);
		as->byte_code[as->byte++] = b[3];
		as->byte_code[as->byte++] = b[2];
		as->byte_code[as->byte++] = b[1];
		as->byte_code[as->byte++] = b[0];
	}
}

void	write_to_byte_code(t_asm *as)
{
	t_list	*lst;
	t_line	*ln;
	int		arg;

	lst = as->lines_list;
	while (lst)
	{
		ft_realloc(as);
		ln = (t_line *)lst->content;
		if (ft_strlen(ln->op) == 0)
		{
			lst = lst->next;
			continue;
		}
		as->byte_code[as->byte++] = g_op_tab[get_index(ln->op)].op_code;
		if (g_op_tab[get_index(ln->op)].coding_byte)
			as->byte_code[as->byte++] = get_coding_byte(ln);
		arg = 0;
		while (arg < g_op_tab[get_index(ln->op)].args_nbr)
			write_arg(as, ln->args[arg++], get_index(ln->op), ln);
		lst = lst->next;
	}
}
