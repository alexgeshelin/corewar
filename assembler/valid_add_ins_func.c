/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_add_ins_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:48:33 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/20 13:42:03 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_r(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != 'r')
		i++;
	i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '\t')
			i++;
		else
			exit(ft_printf("{%s} is not normal arguments for instruction\n",
						str));
	}
	return (1);
}

int		check_proc(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != DIRECT_CHAR)
		i++;
	i++;
	if (str[i] == '-')
		i++;
	if (str[i] == LABEL_CHAR)
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == COMMENT_CHAR)
			break ;
		else
			exit(ft_printf("{%s} is not normal arguments for instruction\n",
						str));
	}
	return (1);
}

int		check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '\t')
			i++;
		else
			exit(ft_printf("{%s} is not normal arguments for instruction\n",
						str));
	}
	return (1);
}

int		cmd_exist(char *str)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(str, g_op_tab[i].op))
			return (1);
		i++;
	}
	return (0);
}

int		start_argument(t_data *data, char *ar, int i)
{
	while (ar[i])
	{
		if ((ar[i] == 'r' && ft_isdigit(ar[i + 1]) && ft_atoi(&ar[i + 1]) <= 99)
				|| (ft_isdigit(ar[i])))
		{
			data->arguments = 1;
			return (1);
		}
		else if (ar[i] == DIRECT_CHAR)
		{
			if (ar[i + 1] == '-')
				i++;
			if ((ar[i + 1] == LABEL_CHAR) || ft_isdigit(ar[i + 1]))
			{
				data->arguments = 1;
				return (1);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}
