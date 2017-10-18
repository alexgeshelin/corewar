/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:25 by ohesheli          #+#    #+#             */
/*   Updated: 2017/04/26 15:38:27 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	char	memory[MEM_SIZE];
	char	color[MEM_SIZE];
	t_champ	champions[MAX_PLAYERS];
	t_flag	flags;
	t_vars	vars;

	vars.process = NULL;
	ft_bzero(memory, MEM_SIZE);
	flags.d = -1;
	flags.v = 0;
	read_args(argc, argv, champions, &flags);
	init_champions(memory, champions, &(vars.process), color);
	introduce(champions);
	if (flags.v)
		initscr();
	init_vars(champions, &vars, color);
	vars.winner = start_war(memory, vars, flags);
	if (flags.v)
	{
		timeout(11111111);
		getch();
		endwin();
	}
	claim_victory(champions, vars.winner);
	return (0);
}
