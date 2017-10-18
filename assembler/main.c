/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:44:40 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/19 16:00:14 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_num_line = 0;
int g_start_mem_arr_size = 5;
int g_new_mem_arr_size = 1;
int g_i = 0;

static void		create_and_fill(t_asm *as, char *filename)
{
	as->header = (t_header *)malloc(sizeof(t_header));
	as->in_fd = open(filename, O_RDONLY);
	if (as->in_fd == -1)
		std_error();
	if (!validate(as->in_fd, filename))
		exit(1);
	lseek(as->in_fd, 0, 0);
	make_name(as, filename);
	as->out_fd = open(as->name, O_CREAT | O_RDWR, 0644);
	if (as->out_fd == -1)
		std_error();
	as->byte_code = (unsigned char *)malloc(1000);
	if (!as->byte_code)
		std_error();
	as->byte = 0;
	as->lines_list = NULL;
}

static	int		is_empty(char *s)
{
	int flag;

	flag = 0;
	while (*s)
	{
		if (*s == '#' && flag == 0)
			return (1);
		if (*s != ' ' && *s != '\t')
			flag = 1;
		s++;
	}
	if (flag)
		return (0);
	return (1);
}

static int		has_op(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ':' && is_empty(&s[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

static void		add_line(t_asm *as, char *s)
{
	t_line			*line;
	int				i;
	int				start;
	static int		start_pos;
	t_list			*elem;

	line = new_line();
	if (!has_op(s))
	{
		fill_label(line, s, &i, &start);
		line->pos = start_pos;
		elem = ft_lstnew(line, sizeof(t_line));
		ft_lstaddend(&as->lines_list, elem);
		free(line);
		return ;
	}
	if (fill_label(line, s, &i, &start))
		fill_op(line, s, &i, &start);
	fill_args(line, s, &i, &start);
	line->pos = start_pos;
	line->need_bytes = calc_size(line);
	start_pos += line->need_bytes;
	elem = ft_lstnew(line, sizeof(t_line) + sizeof(char *) * 3);
	ft_lstaddend(&as->lines_list, elem);
	free(line);
}

int				main(int ac, char **av)
{
	char	*line;
	t_asm	*as;

	if (!(as = (t_asm *)malloc(sizeof(t_asm))))
		std_error();
	if (ac == 1)
		exit(ft_printf("usage: ./assembler [file]\n"));
	create_and_fill(as, av[ac - 1]);
	while (get_next_line(as->in_fd, &line))
	{
		if (ft_strstr(line, NAME_CMD_STRING))
			write_name(as->in_fd, line, as);
		else if (ft_strstr(line, COMMENT_CMD_STRING))
			write_comment(as->in_fd, line, as);
		else if (*line == '#' || is_empty(line) || ft_strlen(line) == 0)
			;
		else
			add_line(as, line);
		free(line);
	}
	write_to_byte_code(as);
	write_byte_code(as);
	close(as->in_fd);
	close(as->out_fd);
	return (0);
}
