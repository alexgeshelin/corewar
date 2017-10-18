/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_add_lable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:00:10 by nsimonov          #+#    #+#             */
/*   Updated: 2017/06/13 13:02:04 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_copylable(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = LABEL_CHAR;
	dst[i + 1] = '\0';
	return (dst);
}

int		parse_lbl(char *line, t_data *data, int line_nbr)
{
	if (!data->name || !data->comment)
		exit(ft_printf(NAME_AND_COMMENT_FIRST));
	if (check_lable(line, data, line_nbr))
	{
		if (data->lable && !data->name && !data->comment)
			exit(ft_printf(NAME_AND_COMMENT_FIRST));
		return (1);
	}
	ft_printf("Lable {%s} is not exist\n", data->cmd_lbl_name);
	return (0);
}

int		is_lable_char(char lbl)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (lbl == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}
