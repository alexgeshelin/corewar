/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:35:28 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 17:53:46 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 4) & 3) != IND_CODE && ((bytecode >> 2) & 3) == REG_CODE\
	&& ((bytecode >> 4) & 3) && ((bytecode >> 6) & 3)\
	&& arg[2] >= 1 && arg[2] <= REG_NUMBER && vars->total_cycles)
	{
		if (convert_args(memory, bytecode, &(arg[0]), process))
			return ;
		arg[0] = (process->op_pc + (arg[0] + arg[1]) % IDX_MOD + MEM_SIZE)\
		% MEM_SIZE;
		arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
		process->reg[arg[2] - 1] = arg[0];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

void	op_fork(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	t_proc	*new;
	int		arg;
	int		i;

	i = 0;
	process->op_pc = process->pc;
	process->pc = (process->pc + 1) % MEM_SIZE;
	arg = get_arg(memory, &process->pc, DIR_CODE, 1);
	arg = arg % IDX_MOD;
	init_process(vars->processes, (process->op_pc + arg + MEM_SIZE) % MEM_SIZE);
	new = *(vars->processes);
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
}

void	op_lfork(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	t_proc	*new;
	int		arg;
	int		i;

	process->op_pc = process->pc;
	i = 0;
	process->pc = (process->pc + 1) % MEM_SIZE;
	arg = get_arg(memory, &process->pc, DIR_CODE, 1);
	init_process(vars->processes, (process->op_pc + arg + MEM_SIZE) % MEM_SIZE);
	new = *(vars->processes);
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
}

void	op_zjmp(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	int		arg;

	process->op_pc = process->pc;
	process->pc = (process->pc + 1) % MEM_SIZE;
	arg = get_arg(memory, &process->pc, DIR_CODE, 1);
	arg = arg % IDX_MOD;
	if (process->carry && vars->total_cycles)
		process->pc = (process->op_pc + arg + MEM_SIZE) % MEM_SIZE;
}

void	op_lld(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[2];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 2);
	if (((bytecode >> 6) & 3) != REG_CODE && ((bytecode >> 4) & 3) == REG_CODE\
	&& ((bytecode >> 6) & 3)\
	&& (arg[1] <= REG_NUMBER && arg[1] >= 1) && vars->total_cycles)
	{
		if (((bytecode >> 6) & 3) == IND_CODE)
		{
			arg[0] = (process->op_pc + arg[0] + MEM_SIZE) % MEM_SIZE;
			arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
		}
		process->reg[arg[1] - 1] = arg[0];
		if (process->reg[arg[1] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}
