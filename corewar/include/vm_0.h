/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:29:04 by edebise           #+#    #+#             */
/*   Updated: 2018/02/21 16:04:08 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_0_H
# define VM_0_H

# include "libft.h"
# include "op.h"
# define VISU 1

typedef	struct			s_process
{
	int					pc;
	int					r[REG_NUMBER + 1];
	int					carry;
	int					cycle;
	int					nb_live;
	int					step;						// pas d'avancement, correspond a la somme de arg_size[] ou 1 (si octet d'encodage non valide)
	int					encoded;
	int					decoded[MAX_ARGS_NUMBER];
	int					arg_size[MAX_ARGS_NUMBER];
	int					arg[MAX_ARGS_NUMBER];
	int					value[MAX_ARGS_NUMBER];
	struct s_process	*prev;
	struct s_process	*next;
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
	int 				(*op_fn[17])(struct s_all*, t_process*);
	t_process			*process_list;
	int					nb_champ;
	int					flag;
	int					dump;
	int					cycle;
	int					cycle_to_die;
	int					nb_live;
	int					last_live;
	int					nb_checks;
	char				arena[MEM_SIZE];
	char				color[MEM_SIZE];
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
t_process				*vm_new_pro(t_all *all, t_process *father, int pc);
t_process				*vm_add_pro_frt(t_process **list, t_process *new);
t_process				*vm_del_one_pro(t_process **list, t_process *target);
void					vm_del_all_pro(t_process **list);
void					vm_set_process(t_all *all);
int						vm_correct_addr(long addr);
int						vm_get_mem(t_all *all, int addr, int size);
void					vm_put_mem(t_all *all, int in, int addr, int size);
void					vm_put_color(t_all *a, t_process *p, int addr, int sz);
int						vm_check_and_get_args(t_all *a, t_process *p, int op);
int						vm_ajust_addr(int addr);
int						vm_convert_param(t_all *all, int adrr, int size);
void					vm_exec_inst(t_all *all, t_process *proc);
int						vm_live(t_all *all, t_process *process);
int						vm_ld(t_all *all, t_process *proc, int tp_prm[3], int lld);
int						vm_st(t_all *all, t_process *pro);
int						vm_add(t_all *all, t_process *proc);
int						vm_sub(t_all *all, t_process *proc);
int						vm_and(t_all *all, t_process *process);
int						vm_xor(t_all *all, t_process *process);
int						vm_or(t_all *all, t_process *process);
int						vm_zjmp(t_all *all, t_process *proc);
int						vm_fork(t_all *all, t_process *proc, int lfork);

void					vm_print_arena(t_all *all);
void					db_print_process(t_process *proc, int num);
#endif
