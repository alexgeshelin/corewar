/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 09:48:36 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/02 09:48:38 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_magic(int out_fd)
{
	int				i;
	unsigned char	*byte;
	t_header		header;

	header.magic = COREWAR_EXEC_MAGIC;
	byte = (unsigned char *)(&header.magic);
	i = 3;
	while (i != -1)
		ft_putchar_fd(byte[i--], out_fd);
}

void	write_name(int in, char *line, t_asm *as)
{
	int		i;
	char	*tmp;
	char	*tail;

	i = 0;
	while (line[i] != '\"')
		i++;
	i++;
	tmp = ft_strdup(&line[i]);
	while (!ft_strchr(tmp, '\"'))
	{
		get_next_line(in, &tail);
		tmp = ft_strjoin(tmp, "\n");
		tmp = ft_strjoin(tmp, tail);
		free(tail);
	}
	ft_bzero(as->header->prog_name, PROG_NAME_LENGTH);
	i = -1;
	while (tmp[++i] != '\"')
		as->header->prog_name[i] = tmp[i];
	free(tmp);
}

void	write_comment(int in, char *line, t_asm *as)
{
	int		i;
	char	*tmp;
	char	*tail;

	i = 0;
	while (line[i] != '\"')
		i++;
	i++;
	tmp = ft_strdup(&line[i]);
	while (!ft_strchr(tmp, '\"'))
	{
		get_next_line(in, &tail);
		tmp = ft_strjoin(tmp, "\n");
		tmp = ft_strjoin(tmp, tail);
		free(tail);
	}
	ft_bzero(as->header->comment, COMMENT_LENGTH);
	i = -1;
	while (tmp[++i] != '\"')
		as->header->comment[i] = tmp[i];
	free(tmp);
}

void	write_byte_code(t_asm *as)
{
	int				i;
	unsigned char	*byte;

	i = 0;
	write_magic(as->out_fd);
	while (i < PROG_NAME_LENGTH)
		ft_putchar_fd(as->header->prog_name[i++], as->out_fd);
	byte = (unsigned char *)(&as->byte);
	i = 3;
	while (i-- != -1)
		ft_putchar_fd(0, as->out_fd);
	i = 3;
	while (i != -1)
		ft_putchar_fd(byte[i--], as->out_fd);
	i = 0;
	while (i < COMMENT_LENGTH)
		ft_putchar_fd(as->header->comment[i++], as->out_fd);
	i = 3;
	while (i-- != -1)
		ft_putchar_fd(0, as->out_fd);
	i = 0;
	while (i < as->byte)
		ft_putchar_fd(as->byte_code[i++], as->out_fd);
	ft_printf("Writing output program to %s\n", as->name);
}

void	std_error(void)
{
	perror("Oops");
	exit(1);
}
