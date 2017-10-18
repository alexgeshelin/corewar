/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:46:56 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/02 17:16:36 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	claim_victory(t_champ champions[MAX_PLAYERS], int winner)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champions[i].num == winner)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", i + 1,\
			champions[i].head.prog_name);
			break ;
		}
		i++;
	}
}

void	introduce(t_champ champions[MAX_PLAYERS])
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (champions[i].head.magic && i < MAX_PLAYERS)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,\
		champions[i].head.prog_size, champions[i].head.prog_name,\
		champions[i].head.comment);
		i++;
	}
}

void	dump(unsigned char memory[MEM_SIZE], t_proc *processes)
{
	int		i;
	int		j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		ft_printf("0x%0.4x : ", i * 64);
		while (j < 64)
		{
			ft_printf("%0.2x ", memory[i * 64 + j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	free_processes(processes);
	exit(0);
}

void	free_processes(t_proc *processes)
{
	t_proc	*crawler;
	t_proc	*buff;

	crawler = processes;
	while (crawler)
	{
		buff = crawler;
		crawler = crawler->next;
		free(buff);
	}
}
