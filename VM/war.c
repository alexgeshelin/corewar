/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:42:54 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 16:42:55 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		start_war(char memory[MEM_SIZE], t_vars vars, t_flag flags)
{
	while (*(vars.processes))
	{
		vars.cycles = 0;
		vars.lives_count = 0;
		while (vars.cycles < vars.cycle_to_die)
		{
			do_ops(memory, &vars);
			vars.cycles++;
			vars.total_cycles++;
			if (vars.total_cycles == flags.d)
				dump((unsigned char*)memory, *(vars.processes));
			if (flags.v)
				visualise((unsigned char *)memory, vars);
		}
		vars.checks++;
		if (vars.checks == MAX_CHECKS || vars.lives_count > NBR_LIVE)
		{
			vars.cycle_to_die -= CYCLE_DELTA;
			vars.checks = 0;
		}
		time_to_die(&vars);
	}
	return (vars.last_alive);
}

void	time_to_die(t_vars *vars)
{
	t_proc	*prev;
	t_proc	*cur;
	t_proc	*next;

	prev = NULL;
	cur = *(vars->processes);
	while (cur)
	{
		next = cur->next;
		if (!(cur->live))
		{
			if (prev)
				prev->next = cur->next;
			else
				*(vars->processes) = cur->next;
			free(cur);
		}
		else
		{
			cur->live = 0;
			prev = cur;
		}
		cur = next;
	}
	zero_champ_lives(vars);
}

void	zero_champ_lives(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
		vars->champ_lives[i++] = 0;
}

void	do_ops(char memory[MEM_SIZE], t_vars *vars)
{
	t_proc	*crawler;

	crawler = *(vars->processes);
	while (crawler)
	{
		if (!crawler->op)
		{
			if (memory[crawler->pc] > 0 && memory[crawler->pc] <= 16)
				crawler->op = memory[crawler->pc];
			else
				crawler->pc = (crawler->pc + 1) % MEM_SIZE;
		}
		if (crawler->op)
		{
			if (crawler->counter == g_ops[crawler->op - 1].counter)
			{
				g_ops[crawler->op - 1].f_op(memory, crawler, vars);
				crawler->counter = 1;
				crawler->op = 0;
			}
			else
				crawler->counter++;
		}
		crawler = crawler->next;
	}
}
