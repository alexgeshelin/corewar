/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohesheli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:39:19 by ohesheli          #+#    #+#             */
/*   Updated: 2017/06/02 18:16:54 by ohesheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../headers/op.h"
# include "stdlib.h"
# include "unistd.h"
# include "fcntl.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <ncurses.h>

typedef struct	s_proc
{
	int				reg[REG_NUMBER];
	int				pc;
	int				op_pc;
	int				op;
	unsigned int	carry;
	unsigned int	counter;
	unsigned int	live;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_champ
{
	t_header		head;
	int				num;
	char			prog[CHAMP_MAX_SIZE + 1];
}				t_champ;

typedef struct	s_vars
{
	int		cycle_to_die;
	int		total_cycles;
	int		checks;
	int		lives_count;
	int		last_alive;
	int		cycles;
	int		nums[MAX_PLAYERS];
	int		champ_lives[MAX_PLAYERS];
	char	*color;
	t_proc	**processes;
	t_proc	*process;
	int		winner;
}				t_vars;

typedef struct	s_flag
{
	int				d;
	int				v;
}				t_flag;

typedef	struct	s_op_tab
{
	int		flag;
}				t_op_tab;

static t_op_tab	g_op_tab[16] =
{
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{1},
	{0}
};

typedef struct	s_ops
{
	void			(*f_op)(char memory[MEM_SIZE], t_proc *process,\
			t_vars *vars);
	unsigned int	counter;
}				t_ops;

static char		*g_error[7] =
{
	"Error: can't open champion.",
	"Error: invalid champion",
	"Error: champion has wrong size",
	"Error: champion is too big",
	"Error: no champions",
	"Error: champions have same numbers",
	"Error: too much champions"
};

void			init_champions(char memory[MEM_SIZE],\
t_champ champions[MAX_PLAYERS], t_proc **processes, char color[MEM_SIZE]);
void			init_process(t_proc **processes, int pc);
void			inject_champion(char memory[MEM_SIZE], t_champ champion,\
				unsigned int i, char color[MEM_SIZE]);
void			read_args(int argc, char **argv,\
				t_champ champions[MAX_PLAYERS], t_flag *flags);
int				check_numbers(t_champ champions[MAX_PLAYERS]);
void			set_number(char *num, char *champ,\
				t_champ champions[MAX_PLAYERS], int j);
void			read_champion(char *champ, t_champ champions[MAX_PLAYERS],\
				int j);
void			invalid(int n);
void			dump(unsigned char memory[MEM_SIZE], t_proc *processes);
void			introduce(t_champ champions[MAX_PLAYERS]);
int				read_number(int fd);
void			free_processes(t_proc *processes);
void			op_live(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			init_vars(t_champ champions[MAX_PLAYERS], t_vars *vars,\
				char color[MEM_SIZE]);
int				start_war(char memory[MEM_SIZE], t_vars vars, t_flag flags);
void			time_to_die(t_vars *vars);
void			zero_champ_lives(t_vars *vars);
void			do_ops(char memory[MEM_SIZE], t_vars *vars);
void			op_aff(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_sti(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_lldi(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_ldi(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_fork(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_lfork(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_zjmp(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_lld(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_ld(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_xor(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_and(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_or(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
int				convert_args(char memory[MEM_SIZE], char bytecode,\
		int *arg, t_proc *process);
void			op_sub(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_add(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			op_st(char memory[MEM_SIZE], t_proc *process, t_vars *vars);
void			store_in_memory(char memory[MEM_SIZE], int arg[2],\
				t_proc *process, t_vars *vars);
void			get_args(char memory[MEM_SIZE], t_proc *process,\
				int *args, int n);
int				get_arg(char memory[MEM_SIZE], int *index, int code, int size);
void			claim_victory(t_champ champions[MAX_PLAYERS], int winner);
int				convert_args_sti(char memory[MEM_SIZE], char bytecode,\
				int *arg, t_proc *process);
int				convert_args_lldi(char memory[MEM_SIZE], char bytecode,\
				int *arg, t_proc *process);
void			visualise(unsigned char *memory, t_vars vars);
void			key_hook(void);
void			print_memory(unsigned char *memory, char *colors);
void			print_info(t_vars vars, int proc_cnt);
void			print_processes(unsigned char *memory, t_vars vars);

static t_ops	g_ops[16] =
{
	{&op_live, 10},
	{&op_ld, 5},
	{&op_st, 5},
	{&op_add, 10},
	{&op_sub, 10},
	{&op_and, 6},
	{&op_or, 6},
	{&op_xor, 6},
	{&op_zjmp, 20},
	{&op_ldi, 25},
	{&op_sti, 25},
	{&op_fork, 800},
	{&op_lld, 10},
	{&op_lldi, 50},
	{&op_lfork, 1000},
	{&op_aff, 2}
};

#endif
