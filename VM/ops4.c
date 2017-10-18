/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:37:51 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 17:56:19 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_sub(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 6) & 3) == REG_CODE && ((bytecode >> 4) & 3) == REG_CODE\
	&& ((bytecode >> 2) & 3) == REG_CODE && vars->total_cycles)
	{
		if (!(arg[0] <= REG_NUMBER && arg[0] >= 1) ||\
			!(arg[1] <= REG_NUMBER && arg[1] >= 1) ||\
			!(arg[2] <= REG_NUMBER && arg[2] >= 1))
			return ;
		process->reg[arg[2] - 1] = process->reg[arg[0] - 1] -\
		process->reg[arg[1] - 1];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

void	op_add(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 6) & 3) == REG_CODE && ((bytecode >> 4) & 3) == REG_CODE\
	&& ((bytecode >> 2) & 3) == REG_CODE && vars->total_cycles)
	{
		if (!(arg[0] <= REG_NUMBER && arg[0] >= 1) ||\
			!(arg[1] <= REG_NUMBER && arg[1] >= 1) ||\
			!(arg[2] <= REG_NUMBER && arg[2] >= 1))
			return ;
		process->reg[arg[2] - 1] = process->reg[arg[0] - 1] +\
		process->reg[arg[1] - 1];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

void	op_st(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[2];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 2);
	if (((bytecode >> 6) & 3) == REG_CODE && ((bytecode >> 4) & 3) != DIR_CODE\
	&& ((bytecode >> 4) & 3) && arg[0] <= REG_NUMBER && arg[0] >= 1)
	{
		if (((bytecode >> 4) & 3) == REG_CODE)
		{
			if (!(arg[1] <= REG_NUMBER && arg[1] >= 1))
				return ;
			process->reg[arg[1] - 1] = process->reg[arg[0] - 1];
			if (process->reg[arg[1] - 1])
				process->carry = 0;
			else
				process->carry = 1;
		}
		else
		{
			arg[1] = (arg[1] % IDX_MOD + process->op_pc + MEM_SIZE) % MEM_SIZE;
			store_in_memory(memory, arg, process, vars);
		}
	}
}

void	store_in_memory(char memory[MEM_SIZE], int arg[2], t_proc *process,\
		t_vars *vars)
{
	int		shift;
	int		i;
	int		color;

	i = 0;
	color = 0;
	while (i < MAX_PLAYERS)
	{
		if (vars->nums[i] == process->reg[0])
		{
			color = i;
			break ;
		}
		i++;
	}
	i = 0;
	shift = 8 * 3;
	while (i < 4)
	{
		vars->color[arg[1]] = color + 1;
		memory[arg[1]] = (process->reg[arg[0] - 1] >> shift) & 255;
		arg[1] = (arg[1] + 1) % MEM_SIZE;
		shift -= 8;
		i++;
	}
}

void	get_args(char memory[MEM_SIZE], t_proc *process,\
		int *args, int n)
{
	int		bytecode;
	int		size;
	int		shift;
	int		i;

	shift = 6;
	i = 0;
	size = g_op_tab[(int)memory[process->pc] - 1].flag;
	process->pc = (process->pc + 1) % MEM_SIZE;
	bytecode = memory[process->pc];
	process->pc = (process->pc + 1) % MEM_SIZE;
	while (n--)
	{
		args[i] = get_arg(memory, &process->pc, (bytecode >> shift) & 3, size);
		shift -= 2;
		i++;
	}
}
