/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:33:37 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 17:52:08 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg;

	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &arg, 1);
	if (((bytecode >> 6) & 3) == REG_CODE && arg >= 1 && arg <= REG_NUMBER &&\
	vars->total_cycles)
	{
		arg = process->reg[arg - 1] % 256;
		write(1, &arg, 1);
	}
}

void	op_sti(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 2) & 3) != IND_CODE && ((bytecode >> 6) & 3) == REG_CODE\
	&& ((bytecode >> 2) & 3) && ((bytecode >> 4) & 3) &&\
	arg[0] >= 1 && arg[0] <= REG_NUMBER && vars->total_cycles)
	{
		if (convert_args_sti(memory, bytecode, &(arg[1]), process))
			return ;
		arg[1] = (process->op_pc + (arg[1] + arg[2]) % IDX_MOD + MEM_SIZE)\
		% MEM_SIZE;
		store_in_memory(memory, arg, process, vars);
	}
}

int		convert_args_sti(char memory[MEM_SIZE], char bytecode,\
		int *arg, t_proc *process)
{
	if (((bytecode >> 4) & 3) == REG_CODE)
	{
		if (!(arg[0] <= REG_NUMBER && arg[0] >= 1))
			return (1);
		arg[0] = process->reg[arg[0] - 1];
	}
	if (((bytecode >> 2) & 3) == REG_CODE)
	{
		if (!(arg[1] <= REG_NUMBER && arg[1] >= 1))
			return (1);
		arg[1] = process->reg[arg[1] - 1];
	}
	if (((bytecode >> 4) & 3) == IND_CODE)
	{
		arg[0] = (process->op_pc + (arg[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
		arg[0] = get_arg(memory, &(arg[0]), DIR_CODE, 0);
	}
	return (0);
}

void	op_lldi(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
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
		if (convert_args_lldi(memory, bytecode, &(arg[0]), process))
			return ;
		arg[0] = (process->op_pc + arg[0] + arg[1] + MEM_SIZE) % MEM_SIZE;
		arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
		process->reg[arg[2] - 1] = arg[0];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

int		convert_args_lldi(char memory[MEM_SIZE], char bytecode,\
		int *arg, t_proc *process)
{
	if (((bytecode >> 4) & 3) == REG_CODE)
	{
		if (!(arg[1] <= REG_NUMBER && arg[1] >= 1))
			return (1);
		arg[1] = process->reg[arg[1] - 1];
	}
	if (((bytecode >> 6) & 3) == REG_CODE)
	{
		if (!(arg[0] <= REG_NUMBER && arg[0] >= 1))
			return (1);
		arg[0] = process->reg[arg[0] - 1];
	}
	if (((bytecode >> 4) & 3) == IND_CODE)
	{
		arg[1] = (process->op_pc + arg[1] + MEM_SIZE) % MEM_SIZE;
		arg[1] = get_arg(memory, &arg[1], DIR_CODE, 0);
	}
	if (((bytecode >> 6) & 3) == IND_CODE)
	{
		arg[0] = (process->op_pc + arg[0] + MEM_SIZE) % MEM_SIZE;
		arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
	}
	return (0);
}
