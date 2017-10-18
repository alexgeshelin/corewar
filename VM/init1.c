/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:39:54 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/02 18:06:12 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_champions(char memory[MEM_SIZE], t_champ champions[MAX_PLAYERS], \
		t_proc **processes, char color[MEM_SIZE])
{
	unsigned int	n;
	unsigned int	i;

	n = 0;
	i = 0;
	if (!check_numbers(champions))
		invalid(5);
	while (champions[n].head.magic && n < MAX_PLAYERS)
		n++;
	while (i < MEM_SIZE)
	{
		color[i] = 0;
		i++;
	}
	i = 0;
	while (i < n)
	{
		inject_champion(memory, champions[i], (MEM_SIZE / n) * i, color);
		init_process(processes, (MEM_SIZE / n) * i);
		(*processes)->reg[0] = champions[i].num;
		i++;
	}
}

void	init_process(t_proc **processes, int pc)
{
	t_proc	*process;
	int		i;

	i = 1;
	process = (t_proc*)malloc(sizeof(t_proc));
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	process->pc = pc;
	process->counter = 1;
	process->carry = 0;
	process->op = 0;
	process->live = 0;
	process->next = *processes;
	*processes = process;
}

void	inject_champion(char memory[MEM_SIZE], t_champ champion,\
						unsigned int i, char color[MEM_SIZE])
{
	unsigned int	j;
	static int		col = 1;

	j = 0;
	while (j < champion.head.prog_size)
	{
		color[i] = col;
		memory[i] = champion.prog[j];
		i++;
		j++;
	}
	col++;
}

void	read_args(int argc, char **argv, t_champ champions[MAX_PLAYERS],\
				t_flag *flags)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (j < MAX_PLAYERS)
		champions[j++].head.magic = 0;
	j = 0;
	while (i < argc)
	{
		if (ft_strequ("-d", argv[i]) && i + 1 < argc)
			flags->d = ft_atoi(argv[++i]);
		else	if (ft_strequ("-v", argv[i]))
			flags->v = 1;
		else	if (j == 4)
			invalid(6);
		else	if (ft_strequ("-n", argv[i]) && i + 2 < argc && (i += 2))
			set_number(argv[i - 1], argv[i], champions, j++);
		else
			set_number(NULL, argv[i], champions, j++);
		i++;
	}
	if (j == 0)
		invalid(4);
}

int		check_numbers(t_champ champions[MAX_PLAYERS])
{
	int		n;
	int		i;
	int		j;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		j = i + 1;
		if (champions[i].head.magic)
			n = champions[i].num;
		else
			break ;
		while (j < MAX_PLAYERS && champions[j].head.magic)
		{
			if (champions[i].num == champions[j].num)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
