/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:39:59 by vtymchen          #+#    #+#             */
/*   Updated: 2017/05/19 17:40:03 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_code(const char *s)
{
	if (*s == 'r')
		return (REG_CODE);
	else if (*s == '%')
		return (DIR_CODE);
	else
		return (IND_CODE);
}

int		get_index(const char *line)
{
	int		i;

	i = 0;
	if (*line == '\0')
		return (16);
	while (i < 16)
	{
		if (ft_strequ(line, g_op_tab[i].op))
			break ;
		i++;
	}
	return (i);
}

int		get_pos(t_asm *as, const char *s)
{
	t_list *l;
	t_line *lst_line;

	l = as->lines_list;
	while (l)
	{
		lst_line = (t_line *)l->content;
		if (ft_strequ(lst_line->label, s))
			break ;
		l = l->next;
	}
	return (lst_line->pos);
}

int		calc_size(t_line *line)
{
	int		size;
	int		arg_nbr;

	arg_nbr = 0;
	size = 1;
	if (g_op_tab[get_index(line->op)].coding_byte)
		size++;
	while (arg_nbr < g_op_tab[get_index(line->op)].args_nbr)
	{
		if (get_code(line->args[arg_nbr]) == REG_CODE)
			size++;
		if (get_code(line->args[arg_nbr]) == IND_CODE)
			size += 2;
		if (get_code(line->args[arg_nbr]) == DIR_CODE &&  \
			g_op_tab[get_index(line->op)].flag)
			size += 2;
		if (get_code(line->args[arg_nbr]) == DIR_CODE &&  \
			!g_op_tab[get_index(line->op)].flag)
			size += 4;
		arg_nbr++;
	}
	return (size);
}

void	make_name(t_asm *as, const char *filename)
{
	int		i;

	as->name = ft_strnew(ft_strlen(filename) + 4);
	i = 0;
	while (filename[i + 1])
	{
		if (filename[i] == '.' && filename[i + 1] == 's')
			break ;
		as->name[i] = filename[i];
		i++;
	}
	as->name[i++] = '.';
	as->name[i++] = 'c';
	as->name[i++] = 'o';
	as->name[i] = 'r';
}
