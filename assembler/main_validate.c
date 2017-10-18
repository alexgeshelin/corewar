/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 12:36:01 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/19 18:51:57 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

int	line_is_empty(char *line)
{
	int len;
	int i;
	int count;

	len = (int)ft_strlen(line);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			count++;
		else
			count--;
		i++;
	}
	if (count == len)
		return (1);
	else
		return (0);
}

int	check_other(t_data *data, int i)
{
	if (!parse_lbl(data->array[i], data, i))
		return (0);
	if (!parse_cmd(data->array[i], data))
		return (0);
	return (1);
}

int	check_name_comm(t_data *data)
{
	int j;

	j = 0;
	while (data->array[data->cnt][j] == ' ' ||
	data->array[data->cnt][j] == '\t')
		j++;
	if (!ft_strncmp(&data->array[data->cnt][j], NAME_CMD_STRING, 4))
	{
		check_name(data->cnt, &data->array[data->cnt][j], data, -1);
		return (1);
	}
	if (!ft_strncmp(&data->array[data->cnt][j], COMMENT_CMD_STRING, 7))
	{
		check_comment(data->cnt, &data->array[data->cnt][j], data, -1);
		return (1);
	}
	return (0);
}

int	parse_file(t_data *data)
{
	data->cnt = 0;
	while (data->array[data->cnt])
	{
		if (!ft_strcmp(data->array[data->cnt], "") ||
				!ft_strcmp(data->array[data->cnt], "\t")
				|| line_is_empty(data->array[data->cnt]))
		{
			data->cnt++;
			continue ;
		}
		if (check_name_comm(data))
		{
			data->cnt++;
			continue ;
		}
		if (!check_other(data, data->cnt))
			return (0);
		data->cnt++;
	}
	return (1);
}

int	validate(int fd, char *prog_name)
{
	t_data	*data;
	int		i;

	data = (t_data*)malloc(sizeof(*data));
	ft_memset(data, 0, sizeof(*data));
	init_mas(data);
	if (!check_prog_name(prog_name))
		return (0);
	make_array(data);
	if (!copy_file_to_array(data, fd))
		return (0);
	if (!parse_file(data))
		return (0);
	if (!check_again(data))
		return (0);
	i = 0;
	while (i < g_i)
	{
		free(data->array[i]);
		i++;
	}
	free(data->array);
	free(data);
	return (1);
}
