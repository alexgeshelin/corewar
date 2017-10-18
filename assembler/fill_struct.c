/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:39:51 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/07 17:39:53 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		fill_label(t_line *l, char *s, int *i, int *start)
{
	int flag;

	*start = 0;
	flag = 0;
	*i = 0;
	while ((s[*i] == '\t' || s[*i] == ' ') && s[*i])
		(*i)++;
	*start = *i;
	while (s[*i] != ' ' && s[*i] != '\t' && s[*i])
		(*i)++;
	s[*i] = '\0';
	if (s[*i - 1] == ':')
	{
		s[*i - 1] = '\0';
		l->label = ft_strdup(&s[*start]);
		flag = 1;
	}
	else
	{
		free(l->op);
		l->op = ft_strdup(&s[*start]);
	}
	(*i)++;
	return (flag);
}

void	fill_op(t_line *l, char *s, int *i, int *start)
{
	free(l->op);
	while ((s[*i] == '\t' || s[*i] == ' ') && s[*i])
		(*i)++;
	*start = *i;
	while (s[*i] != ' ' && s[*i] != '\t' && s[*i])
		(*i)++;
	s[*i] = '\0';
	l->op = ft_strdup(&s[*start]);
	(*i)++;
}

void	fill_args(t_line *line, char *s, int *i, int *start)
{
	int args_nbr;
	int j;

	args_nbr = g_op_tab[get_index(line->op)].args_nbr;
	j = 0;
	while (args_nbr--)
	{
		while ((s[*i] == '\t' || s[*i] == ' ' || s[*i] == ',') && s[*i])
			(*i)++;
		*start = *i;
		while (s[*i] != ' ' && s[*i] != '\t' && s[*i] != ',' && s[*i])
			(*i)++;
		s[*i] = '\0';
		line->args[j++] = ft_strdup(&(s[*start]));
		(*i)++;
	}
}

t_line	*new_line(void)
{
	t_line *line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		std_error();
	line->label = NULL;
	line->args = (char **)malloc(3 * sizeof(char *));
	line->args[0] = NULL;
	line->args[1] = NULL;
	line->args[2] = NULL;
	line->op = ft_strdup("");
	line->need_bytes = 0;
	return (line);
}

void	ft_realloc(t_asm *as)
{
	g_realloc++;
	if (g_realloc == 10)
	{
		as->byte_code = (unsigned char *)realloc((void *)as->byte_code, \
		as->byte + 100);
		if (!as->byte_code)
			std_error();
		g_realloc = 0;
	}
}
