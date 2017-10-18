/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 11:13:51 by vtymchen          #+#    #+#             */
/*   Updated: 2017/03/14 16:42:08 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*new;

	s1 = (s1 == NULL) ? ft_strdup("") : s1;
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	ft_memdel((void **)&s1);
	ft_memdel((void **)&s2);
	return (new);
}

static	int		check_str(char **str, char **line)
{
	char *tmp;

	tmp = ft_strchr(*str, '\n');
	if (tmp)
	{
		*tmp = '\0';
		*line = ft_strdup(*str);
		tmp = ft_strdup(tmp + 1);
		free(*str);
		*str = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char *str = NULL;
	int			in;
	char		*buff;

	if (!line)
		return (-1);
	if (str && check_str(&str, line))
		return (1);
	buff = ft_strnew(BUFF_SIZE);
	while ((in = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[in] = '\0';
		str = ft_my_strjoin(str, buff);
		if (check_str(&str, line))
			return (1);
		buff = ft_strnew(BUFF_SIZE);
	}
	free(buff);
	if (in == -1 || str == NULL)
		return (-1);
	if (in == 0 && *str == '\0')
		return (0);
	*line = ft_strdup(str);
	*str = '\0';
	return (1);
}
