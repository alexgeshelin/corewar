/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_add_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:42:31 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/13 12:42:51 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	count_line(t_data *data)
{
	int i;

	i = 0;
	while (data->array[i])
		i++;
	return (i);
}

int	check_prog_name(char *prog_name)
{
	int	len;

	len = (int)ft_strlen(prog_name) - 1;
	while (prog_name[len] && len > 0)
	{
		if (prog_name[len] == 's' && prog_name[len - 1] == '.' && len >= 2)
			return (1);
		len--;
	}
	ft_printf(PROG_NAME_ERROR);
	return (0);
}

int	check_again(t_data *data)
{
	if ((data->name && !data->comment) || (!data->name && data->comment))
	{
		ft_printf("Name and comment is necessary in champion\n");
		return (0);
	}
	if (!data->lable && !data->cmd && data->name && data->comment)
	{
		ft_printf("It cant be null file after name and comment!\n");
		return (0);
	}
	if (!data->lable && !data->cmd && !data->name && !data->comment)
		exit(ft_printf("Empty file\n"));
	return (1);
}

int	take_index_by_name(char *name_cmd)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (!ft_strcmp(g_op_tab[i].op, name_cmd))
			break ;
		i++;
	}
	return (i);
}

int	ft_wordequ(char *string_to_find, char *ins[])
{
	char	*tmp;
	int		k;

	k = 0;
	while (ins[k])
	{
		tmp = find_cmd_in_string(string_to_find, ins[k]);
		if (tmp)
			return (1);
		k++;
	}
	return (0);
}
