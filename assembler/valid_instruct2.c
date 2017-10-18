/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_instruct2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:37:38 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/20 13:41:31 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_str(char *str, int i, t_data *data, int size_st)
{
	int j;

	j = 0;
	if (i >= size_st)
		return (1);
	ft_memset(data->cmp, 0, sizeof(data->cmp));
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
		data->cmp[j++] = str[i++];
	if (cmd_exist(data->cmp))
		data->find_cmd++;
	else if (data->cmp[ft_strlen(data->cmp) - 1] == LABEL_CHAR ||
			data->cmp[0] == LABEL_CHAR)
	{
		data->flag_for_lable = 1;
		ft_memset(data->cmp, 0, sizeof(data->cmp));
	}
	else if (start_argument(data, data->cmp, 0))
		return (1);
	else
		exit(ft_printf(NOT_VALID_LINE, data->cmp));
	check_str(str, i, data, size_st);
	return (0);
}

void	clear_variable(t_data *data)
{
	data->flag_for_lable = 0;
	data->find_cmd = 0;
	data->arguments = 0;
}

void	check_result(t_data *data, char *line)
{
	if (data->find_cmd > 1)
		exit(ft_printf(ONE_INSTRUCT_PER_LINE));
	else if ((!data->find_cmd && !data->flag_for_lable) ||
			(!data->find_cmd && data->flag_for_lable && data->arguments))
		exit(ft_printf(ARG_WITHOUT_INS, line));
	else if (data->find_cmd && !data->arguments)
		exit(ft_printf(INS_WITHOUT_ARG, line));
}

int		check_cmd_and_args(char *line, t_data *data)
{
	int		i;
	char	*instruction;
	int		len;

	i = 0;
	len = 0;
	check_str(line, 0, data, (int)ft_strlen(line) - 1);
	check_result(data, line);
	clear_variable(data);
	while (data->instruct_name[i])
	{
		instruction = find_cmd_in_string(line, data->instruct_name[i]);
		if (instruction)
		{
			len = (int)ft_strlen(instruction);
			if (instruction[len - 1] == LABEL_CHAR ||
					instruction[len - 2] == LABEL_CHAR)
				break ;
			check_cmd(instruction, data, data->instruct_name[i]);
		}
		i++;
	}
	return (1);
}

int		parse_cmd(char *line, t_data *data)
{
	int i;

	i = 0;
	if (!data->name || !data->comment)
		exit(ft_printf(NAME_AND_COMMENT_FIRST));
	while (line[i])
	{
		if (line[i] == ',' || line[i] == 'r' || line[i] == DIRECT_CHAR)
		{
			if (line[i] == 'r' && !ft_isdigit(line[i + 1]))
				break ;
			data->arguments++;
		}
		i++;
	}
	if (check_cmd_and_args(line, data))
	{
		if (data->cmd && !data->name && !data->comment)
			exit(ft_printf(NAME_AND_COMMENT_FIRST));
		return (1);
	}
	if (data->no_args || data->no_correct)
		return (0);
	return (1);
}
