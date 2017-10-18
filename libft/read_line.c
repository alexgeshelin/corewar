/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsimonov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:29:48 by nsimonov          #+#    #+#             */
/*   Updated: 2017/03/28 20:08:19 by nsimonov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int		check_buff(char *buff, char **line)
{
	int i;
	int j;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == '\n')
	{
		buff[i] = '\0';
		*line = ft_strjoin_frees1(*line, buff);
		i++;
		j = 0;
		while (buff[i] != '\0')
			buff[j++] = buff[i++];
		buff[j] = '\0';
		return (1);
	}
	*line = ft_strjoin_frees1(*line, buff);
	free(buff);
	return (0);
}

int		ft_read(int const fd, char *temp, char **line, char *buff)
{
	int	i;
	int	rd;
	int	j;

	while ((rd = read(fd, temp, BUFF_SIZE)) > 0)
	{
		i = 0;
		while (temp[i] != '\n' && i < rd)
			i++;
		if (temp[i] == '\n')
		{
			temp[i++] = '\0';
			j = 0;
			while (i < rd)
				buff[j++] = temp[i++];
			buff[j] = '\0';
			*line = ft_strjoin_frees1(*line, temp);
			free(temp);
			return (1);
		}
		temp[i] = '\0';
		*line = ft_strjoin_frees1(*line, temp);
	}
	free(temp);
	return (0);
}

int		help(t_mylist *head, int fd, char *temp, char **line)
{
	head[fd].buff = ft_strnew(BUFF_SIZE);
	if (head[fd].buff == NULL)
		return (0);
	if ((ft_read(fd, temp, line, head[fd].buff)) == 1)
	{
		ft_strdel(&(head[fd].buff));
		return (1);
	}
	return (1);
}

int		read_line(int const fd, char **line)
{
	char			*temp;
	static t_mylist	head[OPEN_MAX];

	if ((BUFF_SIZE <= 0 || (read(fd, NULL, 0) == -1) || line == NULL))
		return (-1);
	if ((*line = ft_strnew(1)) == NULL)
		return (0);
	if (head[fd].buff != NULL)
	{
		if ((check_buff(head[fd].buff, line)) == 1)
			return (1);
	}
	else
	{
		temp = ft_strnew(BUFF_SIZE);
		if (help(head, fd, temp, line))
			return (1);
		return (0);
	}
	return (0);
}
