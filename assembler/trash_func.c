/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 12:25:15 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/19 12:28:22 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_fake(char *str, int i, char *instr)
{
	if ((!ft_strcmp(instr, "st") && str[i + 2] == 'i' &&
				str[i + 1] != '\0') ||
			(!ft_strcmp(instr, "st") && str[i + 2] != '\t'
			&& str[i + 2] != ' ' && str[i + 1] != '\0') ||
			(!ft_strcmp(instr, "or") && str[i + 2] != ' ' &&
			str[i + 2] != '\t' && str[i + 1] != '\0') ||
			(!ft_strcmp(instr, "live") && str[i - 1] != ' ' &&
			str[i - 1] != '\t' && str[i - 1]) ||
			(!ft_strcmp(instr, "live") && str[i + 4] != ' ' &&
			str[i + 4] != '\t' && str[i + 4]) ||
			(!ft_strcmp(instr, "ld") && str[i + 2] != ' ' &&
			str[i + 2] != '\t') ||
			(!ft_strcmp(instr, "fork") && str[i + 4] != ' ' &&
			str[i + 4] != '\t' && str[i + 4]) ||
			(!ft_strcmp(instr, "sti") && str[i + 3] != '\t' &&
			str[i + 3] != ' ' && str[i + 3] != '\0'))
		return (1);
	return (0);
}

void	init_mas(t_data *data)
{
	data->instruct_name[0] = "lldi";
	data->instruct_name[1] = "ld";
	data->instruct_name[2] = "sti";
	data->instruct_name[3] = "add";
	data->instruct_name[4] = "sub";
	data->instruct_name[5] = "and";
	data->instruct_name[6] = "or";
	data->instruct_name[7] = "xor";
	data->instruct_name[8] = "zjmp";
	data->instruct_name[9] = "ldi";
	data->instruct_name[10] = "aff";
	data->instruct_name[11] = "fork";
	data->instruct_name[12] = "lld";
	data->instruct_name[13] = "live";
	data->instruct_name[14] = "lfork";
	data->instruct_name[15] = "st";
	data->instruct_name[16] = NULL;
}
