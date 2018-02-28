/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:29:04 by edebise           #+#    #+#             */
/*   Updated: 2018/02/28 00:00:08 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_0_H
# define VM_0_H

# include "libft.h"
# include "op.h"
# include <ncurses.h>
# include <unistd.h>
# define VISU 1
# define DUMP 2

# define P0_COL		1
# define P1_COL		2
# define P2_COL		3
# define P3_COL		4
# define P4_COL		5
# define P0_COL_PC	6
# define P1_COL_PC	7
# define P2_COL_PC	8
# define P3_COL_PC	9
# define P4_COL_PC	10
# define BORDER_COL	11
# define SELECT_PC	12

# define MARGE_PROC	34

typedef	struct			s_process
{
	int					pc;
	int					r[REG_NUMBER + 1];
	int					carry;
	int					cycle;
	int					nb_live;
	int					step;
	int					encoded;
	int					decoded[MAX_ARGS_NUMBER];
	int					arg_size[MAX_ARGS_NUMBER];
	int					arg[MAX_ARGS_NUMBER];
	int					value[MAX_ARGS_NUMBER];
	struct s_process	*prev;
	struct s_process	*next;
	int					op;
	int					nb;
}						t_process;

typedef	struct			s_champ
{
	t_header			header;
	char				*path;
	char				prog[CHAMP_MAX_SIZE];
	int					prog_size;
	int					fd;
	int					nb;
	char				color[10];
	struct s_champ		*prev;
	struct s_champ		*next;
}						t_champ;

typedef	struct			s_all
{
	t_champ				champ[MAX_PLAYERS];
	void 				(*op_fn[17])(struct s_all*, t_process*);
	t_process			*process_list;
	int					nb_champ;
	int					nb_process;
	int					flag;
	int					dump;
	int					cycle;
	int					cycle_delta;
	int					cycle_to_die;
	int					nb_live;
	int					last_live;
	int					nb_checks;
	int					aff_str_size;
	char				*aff_str;
	char				*gnl;
	char				arena[MEM_SIZE];
	char				color[MEM_SIZE];
	WINDOW				*win_arena;
	WINDOW				*win_info;
	WINDOW				*win_proc;
	WINDOW				*win_dial;
	int					cycles_sec;
	useconds_t			time_step;
	int					pause;
	struct timeval		last_time;
	int					current_proc;
}						t_all;

void					vm_usage(t_all *all, char *error_mail);
int						vm_exit(t_all *all, char *error_mail);
void					*vm_malloc(t_all *all, int size);
void					vm_get_flag(t_all *all, int *n, char **av);
void					vm_get_champ_path(t_all *all, int *n, char **av);
void					vm_get_champs(t_all *all, int buf_size);
void					vm_number_champs(t_all *all);
short					rev_endian_short(short in);
int						rev_endian_int(int in);
void					vm_set_match(t_all *all);
void					vm_run_battle(t_all *all);
void					vm_set_process(t_all *all);
int						vm_check_process(int *tab, int address);
t_process				*vm_new_pro(t_all *all, t_process *father, int pc);
t_process				*vm_add_pro_frt(t_process **list, t_process *new);
t_process				*vm_del_one_pro(t_process **list, t_process *target);
void					vm_del_all_pro(t_process **list);
int						vm_check_and_get_args(t_all *a, t_process *p, int op);
int						vm_ajust_addr(long addr);
int						vm_get_mem(t_all *all, int addr, int size);
void					vm_put_mem(t_all *all, int in, int addr, int size);
void					vm_put_color(t_all *a, t_process *p, int addr, int sz);
void					init_pro_cycle(t_all *all, t_process *proc);
void					vm_live(t_all *all, t_process *process);
void					vm_ld(t_all *all, t_process *process);
void					vm_lld(t_all *all, t_process *proc);
void					vm_ldi(t_all *all, t_process *proc);
void					vm_lldi(t_all *all, t_process *proc);
void					vm_st(t_all *all, t_process *pro);
void					vm_sti(t_all *all, t_process *pro);
void					vm_add(t_all *all, t_process *proc);
void					vm_sub(t_all *all, t_process *proc);
void					vm_and(t_all *all, t_process *process);
void					vm_xor(t_all *all, t_process *process);
void					vm_or(t_all *all, t_process *process);
void					vm_zjmp(t_all *all, t_process *proc);
void					vm_fork(t_all *all, t_process *proc);
void					vm_lfork(t_all *all, t_process *proc);
void					vm_aff(t_all *all, t_process *process);
void					vm_print_winner(t_all *all);

void					vm_print_arena(t_all *all, t_process * process);
void					db_print_process(t_process *proc, int num);
void					vm_visu(t_all *all);
void					vm_init_visu(t_all *all);
void					vm_exit_visu(t_all *all);
void					visu_print(t_all *all, char *format, ...);
void					visu_change_speed(t_all *all, int c);
void					visu_print_info(t_all *all);
void					visu_print_process(t_all *all);
void					visu_print_arena(t_all *all);
void					visu_change_proc(t_all *all, int c);
void					vm_visu_print_players(t_all *all);
void					print_proc(t_all *all, t_process *proc);
void					vm_init_colors(void);

#endif
