/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 18:30:12 by vtymchen          #+#    #+#             */
/*   Updated: 2017/06/01 18:30:16 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			visualise(unsigned char *memory, t_vars vars)
{
	usleep(5000);
	key_hook();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_BLUE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_WHITE, COLOR_BLACK);
	print_memory(memory, vars.color);
	print_processes(memory, vars);
}

void			key_hook(void)
{
	char		ch;
	static int	flag;

	timeout(1);
	ch = getch();
	if (ch == ' ' || flag)
	{
		flag = 1;
		while (flag)
		{
			timeout(1);
			ch = getch();
			if (ch == ' ')
				flag = 0;
			else if (ch == 's')
				break ;
		}
	}
}

void			print_memory(unsigned char *memory, char *colors)
{
	int i;
	int j;

	i = 0;
	move(0, 0);
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			attron(COLOR_PAIR(colors[i * 64 + j] + 1));
			printw("%02x ", memory[i * 64 + j]);
			j++;
			attroff(COLOR_PAIR(colors[i * 64 + j] + 1));
		}
		printw("\n");
		i++;
	}
}

void			print_info(t_vars vars, int proc_cnt)
{
	move(1, 64 * 3 + 4);
	attron(COLOR_PAIR(11));
	attron(A_BOLD);
	curs_set(0);
	printw("Cycle : %i\n", vars.total_cycles);
	move(2, 64 * 3 + 4);
	printw("Processes : %i\n", proc_cnt);
	move(3, 64 * 3 + 4);
	printw("CYCLES_TO_DIE : %i\n", vars.cycle_to_die);
	move(4, 64 * 3 + 4);
	printw("CYCLES_DELTA: %i\n", CYCLE_DELTA);
	move(5, 64 * 3 + 4);
	printw("NBR_LIVE : %i\n", NBR_LIVE);
	move(6, 64 * 3 + 4);
	printw("MAX_CHECKS : %i\n", MAX_CHECKS);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(11));
}

void			print_processes(unsigned char *memory, t_vars vars)
{
	int		proc_cnt;
	t_proc	*proc;

	proc_cnt = 0;
	proc = *(vars.processes);
	while (proc)
	{
		attron(COLOR_PAIR(vars.color[proc->pc] + 1 + 5));
		move(proc->pc / 64, proc->pc % 64 * 3);
		printw("%02x", memory[proc->pc]);
		attroff(COLOR_PAIR(vars.color[proc->pc] + 1 + 5));
		proc = proc->next;
		proc_cnt++;
	}
	print_info(vars, proc_cnt);
	refresh();
}
