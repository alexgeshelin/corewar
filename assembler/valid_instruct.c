/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_instruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:12:08 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/19 12:21:06 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_type(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 'r' && check_r(arg) && ft_isdigit(arg[i + 1]) &&
				ft_atoi(&arg[i + 1]) <= 99)
			return (T_REG);
		else if (arg[i] == DIRECT_CHAR && check_proc(arg))
		{
			if (arg[i + 1] == '-')
				i++;
			if ((arg[i + 1] == LABEL_CHAR) || ft_isdigit(arg[i + 1]))
				return (T_DIR);
			else
				return (0);
		}
		else if (arg[i] >= '0' && arg[i] <= '9' && check_digit(arg))
			return (T_IND);
		else if (arg[i] == LABEL_CHAR)
			return (T_IND);
		i++;
	}
	return (0);
}

int		confirm_cmd(char *args_cmd, char *cmd_name, t_data *data)
{
	int i;

	data->index = take_index_by_name(cmd_name);
	copy_args_to_array(data, args_cmd);
	i = -1;
	while (++i < g_op_tab[data->index].args_nbr)
	{
		if (g_op_tab[data->index].type[i] & get_type(data->array_args[i]))
			continue;
		else
			exit(ft_printf(NOT_VAL_AR_INS, data->array_args[i], cmd_name));
	}
	return (0);
}

int		check_args(char *ins, int count, t_data *data)
{
	if ((!ft_strcmp(ins, "sti") || !ft_strcmp(ins, "add") ||
				!ft_strcmp(ins, "sub") || !ft_strcmp(ins, "and") ||
				!ft_strcmp(ins, "or") || !ft_strcmp(ins, "xor") ||
				!ft_strcmp(ins, "ldi") || !ft_strcmp(ins, "lldi")) &&
			(count == 2))
		return (1);
	if ((!ft_strcmp(ins, "live") || !ft_strcmp(ins, "fork") ||
				!ft_strcmp(ins, "lfork") ||
				!ft_strcmp(ins, "aff") || !ft_strcmp(ins, "zjmp")) &&
			(count == 0))
		return (1);
	if ((!ft_strcmp(ins, "ld") || !ft_strcmp(ins, "st") ||
				!ft_strcmp(ins, "lld")) && (count == 1))
		return (1);
	data->no_args = 1;
	return (0);
}

void	check_cmd(char *line, t_data *data, char *instruct_name)
{
	int i;
	int count;
	int skip;
	int k;

	skip = (int)ft_strlen(instruct_name);
	i = 0;
	count = 0;
	while (i < skip)
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_wordequ(&line[i], data->instruct_name))
		exit(ft_printf(ONE_INSTRUCT_PER_LINE));
	k = i;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
			count++;
		i++;
	}
	if (!check_args(instruct_name, count, data))
		exit(ft_printf(TO_FEW_MUCH_ARG, instruct_name));
	confirm_cmd(&line[k], instruct_name, data);
	data->cmd = 1;
}

char	*find_cmd_in_string(char *find_in, char *instr)
{
	int		i;
	char	*str;

	str = find_in;
	i = 0;
	if (*instr == '\0')
		return (str);
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			break ;
		if (!ft_strncmp(&str[i], instr, ft_strlen(instr)) && str[i - 1] !=
				LABEL_CHAR && str[i + ft_strlen(instr)] != LABEL_CHAR)
		{
			if (is_fake(str, i, instr))
			{
				i++;
				continue;
			}
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
