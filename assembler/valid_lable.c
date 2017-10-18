/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_lable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:44:04 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/20 14:49:46 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		help_confirm_lable(char *line, t_data *data, int count)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] !=
			LABEL_CHAR && line[i] != COMMENT_CHAR)
	{
		if (is_lable_char(line[i]))
			i++;
		else
			exit(ft_printf(NOT_LABLE_CHAR, line[i]));
	}
	i++;
	while (line[i])
	{
		if (line[i] == LABEL_CHAR && is_lable_char(line[i - 1]))
			count++;
		i++;
	}
	if (count)
		exit(printf("Error two lable in line {%s}\n", line));
	data->lable = 1;
	return (1);
}

int		confirm_lbl(char *line, t_data *data, int cmd_lbl)
{
	int i;

	i = 0;
	if (cmd_lbl)
	{
		while (line[i] == ' ' && line[i] == '\t')
			i++;
		while (line[i] && line[i] != SEPARATOR_CHAR && line[i] != '\t' &&
				line[i] != ' ' && line[i] != COMMENT_CHAR)
		{
			if (is_lable_char(line[i]))
				i++;
			else
				exit(ft_printf(NOT_LABLE_CHAR, line[i]));
		}
		data->lable = 1;
		ft_copylable(data->cmd_lbl_name, line, (size_t)i);
		return (1);
	}
	if (!help_confirm_lable(line, data, 0))
		return (0);
	return (1);
}

int		exist_lable(char *lable_name, t_data *data, int line_nbr)
{
	int i;
	int find;

	i = 0;
	find = 0;
	if (!ft_strncmp(lable_name, data->array[line_nbr], ft_strlen(lable_name)))
		find++;
	while (data->array[i])
	{
		if (!ft_strncmp(lable_name, data->array[i], ft_strlen(lable_name)))
		{
			find++;
			if (data->array[i][ft_strlen(lable_name) - 1] != LABEL_CHAR)
				find--;
		}
		i++;
	}
	if (find)
		return (1);
	return (0);
}

int		check_lable(char *line, t_data *data, int line_nbr)
{
	int i;

	i = 0;
	if (line[0] == LABEL_CHAR)
		exit(ft_printf(BEGINNING_LABLE_CHAR));
	while (line[i])
	{
		if ((line[i] == LABEL_CHAR) && (line[i - 1] == DIRECT_CHAR ||
					line[i - 1] == ',' || line[i - 1] == ' '))
		{
			if (!confirm_lbl(&line[i + 1], data, COMMAND_LABLE))
				return (0);
			if (!exist_lable(data->cmd_lbl_name, data, line_nbr))
				return (0);
		}
		if (line[i] == LABEL_CHAR && is_lable_char(line[i - 1]))
		{
			if (!confirm_lbl(line, data, FIRST_LABLE))
				return (0);
		}
		i++;
	}
	return (1);
}
