/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:38:42 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 16:38:43 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	int		arg;
	int		i;

	i = 0;
	vars->lives_count++;
	process->pc = (process->pc + 1) % MEM_SIZE;
	arg = get_arg(memory, &process->pc, DIR_CODE, 0);
	while (i < MAX_PLAYERS)
	{
		if (arg == vars->nums[i])
		{
			vars->last_alive = arg;
			vars->champ_lives[i]++;
			break ;
		}
		i++;
	}
	process->live++;
}

int		get_arg(char memory[MEM_SIZE], int *index, int code, int size)
{
	unsigned int	res;
	unsigned char	*mem;
	int				i;
	int				j;

	mem = (unsigned char*)&(memory[0]);
	if (!code)
		return (0);
	i = 0;
	res = 0;
	if (code == REG_CODE)
		j = 1;
	else	if (code == DIR_CODE && !size)
		j = 4;
	else
		j = 2;
	while (i++ < j)
	{
		res <<= 8;
		res = res | mem[*index];
		*index = (*index + 1) % MEM_SIZE;
	}
	if (j == 2)
		res = (short)res;
	return (res);
}
