/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:41:52 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/02 17:20:46 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			set_number(char *num, char *champ,\
				t_champ champions[MAX_PLAYERS], int j)
{
	static int	i = -1;

	if (num)
		champions[j].num = ft_atoi(num);
	else
	{
		champions[j].num = i;
		i--;
	}
	read_champion(champ, champions, j);
}

void			read_champion(char *champ, t_champ champions[MAX_PLAYERS],\
				int j)
{
	int		fd;

	ft_bzero(champions[j].head.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(champions[j].head.comment, COMMENT_LENGTH + 1);
	ft_bzero(champions[j].prog, CHAMP_MAX_SIZE + 1);
	if ((fd = open(champ, O_RDONLY)) == -1)
		invalid(0);
	if ((champions[j].head.magic = read_number(fd)) != COREWAR_EXEC_MAGIC)
		invalid(1);
	if ((read(fd, champions[j].head.prog_name, PROG_NAME_LENGTH))\
	< PROG_NAME_LENGTH)
		invalid(1);
	lseek(fd, 4, SEEK_CUR);
	if (!(champions[j].head.prog_size = read_number(fd)))
		invalid(1);
	if ((read(fd, champions[j].head.comment, COMMENT_LENGTH)) <\
	COMMENT_LENGTH)
		invalid(1);
	lseek(fd, 4, SEEK_CUR);
	if ((read(fd, champions[j].prog, champions[j].head.prog_size)) <\
	champions[j].head.prog_size || (read(fd, NULL, 1)) != 0)
		invalid(2);
	if (champions[j].head.prog_size > CHAMP_MAX_SIZE)
		invalid(3);
	close(fd);
}

int				read_number(int fd)
{
	unsigned int	res;
	int				i;
	unsigned int	buff;

	i = 0;
	res = 0;
	buff = 0;
	while (i < 4)
	{
		res = res << 8;
		if (!(read(fd, &buff, 1)))
			return (0);
		res = res | buff;
		i++;
	}
	return (res);
}

void			invalid(int n)
{
	ft_printf("%s\n", g_error[n]);
	exit(0);
}

void			init_vars(t_champ champions[MAX_PLAYERS], t_vars *vars,\
				char color[MEM_SIZE])
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champions[i].head.magic == 0)
			vars->nums[i] = vars->nums[0];
		else
		{
			vars->last_alive = champions[i].num;
			vars->nums[i] = champions[i].num;
		}
		vars->champ_lives[i] = 0;
		i++;
	}
	vars->cycle_to_die = CYCLE_TO_DIE;
	vars->total_cycles = 0;
	vars->checks = 0;
	vars->lives_count = 0;
	vars->cycles = 0;
	vars->processes = &(vars->process);
	vars->color = &(color[0]);
}
