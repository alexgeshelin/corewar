/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:36:49 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/01 17:54:53 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ld(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
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
			arg[0] = (process->op_pc + arg[0] % IDX_MOD + MEM_SIZE) % MEM_SIZE;
			arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
		}
		process->reg[arg[1] - 1] = arg[0];
		if (arg[0] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
}

void	op_xor(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 2) & 3) == REG_CODE && ((bytecode >> 4) & 3)\
	&& ((bytecode >> 6) & 3)\
	&& arg[2] <= REG_NUMBER && arg[2] >= 1 && vars->total_cycles)
	{
		if (convert_args(memory, bytecode, &(arg[0]), process))
			return ;
		process->reg[arg[2] - 1] = arg[0] ^ arg[1];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

void	op_and(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 2) & 3) == REG_CODE && ((bytecode >> 4) & 3)\
	&& ((bytecode >> 6) & 3)\
	&& arg[2] <= REG_NUMBER && arg[2] >= 1 && vars->total_cycles)
	{
		if (convert_args(memory, bytecode, &(arg[0]), process))
			return ;
		process->reg[arg[2] - 1] = arg[0] & arg[1];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

void	op_or(char memory[MEM_SIZE], t_proc *process, t_vars *vars)
{
	unsigned char	bytecode;
	int				arg[3];

	process->op_pc = process->pc;
	bytecode = memory[(process->pc + 1) % MEM_SIZE];
	get_args(memory, process, &(arg[0]), 3);
	if (((bytecode >> 2) & 3) == REG_CODE && ((bytecode >> 4) & 3)\
	&& ((bytecode >> 6) & 3)\
	&& arg[2] <= REG_NUMBER && arg[2] >= 1 && vars->total_cycles)
	{
		if (convert_args(memory, bytecode, &(arg[0]), process))
			return ;
		process->reg[arg[2] - 1] = arg[0] | arg[1];
		if (process->reg[arg[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

int		convert_args(char memory[MEM_SIZE], char bytecode,\
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
		arg[1] = (process->op_pc + (arg[1] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
		arg[1] = get_arg(memory, &arg[1], DIR_CODE, 0);
	}
	if (((bytecode >> 6) & 3) == IND_CODE)
	{
		arg[0] = (process->op_pc + (arg[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
		arg[0] = get_arg(memory, &arg[0], DIR_CODE, 0);
	}
	return (0);
}
