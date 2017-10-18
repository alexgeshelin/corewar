/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arr_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:02:43 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/19 15:59:42 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	copy_args_to_array(t_data *data, char *args_cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (i < g_op_tab[data->index].args_nbr)
	{
		k = 0;
		while (args_cmd[j] != ',' && args_cmd[j])
			data->array_args[i][k++] = args_cmd[j++];
		data->array_args[i][k] = '\0';
		j++;
		i++;
	}
}

void	make_array(t_data *data)
{
	data->array = (char **)malloc(sizeof(char *) * (g_start_mem_arr_size + 1));
	if (data->array == NULL)
		return ;
	data->array[g_start_mem_arr_size] = 0;
}

void	copy_file(char *line, t_data *data, int j, int index)
{
	int	new;

	if (g_i > g_start_mem_arr_size)
	{
		new = g_start_mem_arr_size + g_new_mem_arr_size;
		g_new_mem_arr_size++;
		data->array = (char**)realloc(data->array, sizeof(char *) * (new + 1));
	}
	data->array[g_i] = (char *)malloc(sizeof(char *) * ft_strlen(line) + 1);
	if (line[0] == COMMENT_CHAR)
	{
		ft_memdel((void **)&data->array[g_i]);
		return ;
	}
	while (line[index])
	{
		if ((line[index] == COMMENT_CHAR && data->flag_for_name &&
					data->flag_for_com) || (line[index] == ';'))
			break ;
		if (!data->flag_for_name || !data->flag_for_com)
			find_name_cmm(line, data);
		data->array[g_i][j++] = line[index++];
	}
	data->array[g_i++][j] = '\0';
}

void	find_name_cmm(char *line, t_data *data)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!ft_strncmp(&line[i], ".name", 4))
		data->flag_for_name = 1;
	if (!ft_strncmp(&line[i], ".comment", 7))
		data->flag_for_com = 1;
}

int		copy_file_to_array(t_data *data, int fd)
{
	char	*line;
	int		len;

	len = 0;
	while (read_line(fd, &line))
	{
		g_num_line++;
		copy_file(line, data, 0, 0);
		free(line);
	}
	free(line);
	if (data->array[g_i])
		data->array[g_i] = 0;
	len = count_line(data);
	if ((!ft_strcmp("\t", data->array[len - 1]) ||
				!ft_strcmp("", data->array[len - 1]) ||
				!ft_strcmp("\n", data->array[len - 1])))
	{
		return (1);
	}
	ft_printf(UNEXPECTED_INPUT);
	return (0);
}
