/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_4_run_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:59:11 by edebise           #+#    #+#             */
/*   Updated: 2018/02/22 18:23:43 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**
*/

void		db_print_process(t_process *proc, int num)
{
	pf("{c}Process %d{0}\n", num);
	pf("PC : [{g}%d{0}]\nCarry : [{g}%d{0}]\nCycle : [{g}%d{0}]\n", proc->pc, proc->carry, proc->cycle);
	if (proc->nb_live)
		pf("Nb live : [{g}%d{0}]\n", proc->nb_live);
	else
		pf("Nb live : [{r}%d{0}]\n", proc->nb_live);
}

static void	vm_exec_inst(t_all *all, t_process *proc)
{
	char	*gnl;
	int		op;

	proc->step = 1;
	op = vm_get_mem(all, proc->pc, 1);
	if (op > 0 && op < 17)
	{
		all->op_fn[op](all, proc);
		pf("process->pc : %d\n", proc->pc);
		vm_print_arena(all, proc);			//	Debug
		get_next_line(0, &gnl);			//	Debug
		all->op_fn[op](all, proc);
//		sleep(3);
	}
	proc->pc = vm_correct_addr(proc->pc + proc->step);
}

static void	delete_dead_process(t_all *all)
{
	t_process	*current;
	t_process	*tmp;

	current = all->process_list;
	while (current)
	{
		if (!current->nb_live)
		{
			tmp = current->next;
			vm_del_one_pro(&all->process_list, current);
			current = tmp;
		}
		else
		{
			current->nb_live = 0;
			current = current->next;
		}
	}
	all->cycle_to_die = (all->nb_live >= NBR_LIVE) ?
							all->cycle_to_die - CYCLE_DELTA : all->cycle_to_die;
	all->nb_checks = (all->nb_live >= NBR_LIVE) ? 0 : all->nb_checks + 1;
	all->nb_live = 0;
}

static void	manage_cycle(t_all *all)
{
	all->cycle++;
	if (!(all->cycle % all->cycle_to_die))
		delete_dead_process(all);
	if (all->nb_checks >= 10)
	{
		all->cycle_to_die -= CYCLE_DELTA;
		all->nb_checks = 0;
	}
	if (all->cycle_to_die < 0)
		all->cycle_to_die = 0;
//	pf("{y}-------------------------------{0}\n");
//	pf("Cycle Total : [{g}%d{0}]\nCycle to die :[{r}%d{0}]\nNb Checks : [{r}%d{0}]\n", all->cycle, all->cycle_to_die, all->nb_checks);
//	pf("{y}-------------------------------{0}\n");
//	if (!(all->cycle % all->cycle_to_die))
//	 	sleep(3);
}

static void	init_pro_cycle(t_all *all, t_process *proc)
{
	int			op;
	extern t_op	g_op_tab;
	t_op		*tab;

	tab = &g_op_tab;
	if (!proc)
	{
		proc = all->process_list;
		while (proc)
		{
			init_pro_cycle(all, proc);
			proc = proc->next;
		}
	}
	else
	{
		op = vm_get_mem(all, proc->pc, 1);
		if (op >= 1 && op <= 17)
			proc->cycle = (tab[op - 1]).cycles;
	}
}

void	vm_run_battle(t_all *all)
{
	t_process	*current;
	int			db_i;

	init_pro_cycle(all, NULL);
	while (all->cycle_to_die && all->process_list)
	{
//		if (all->flag & VISU)
//			vm_visu(all);
		current = all->process_list;
		db_i = 0;
		while (current)
		{
		//	++(all->cycle);
		//	continue;
		//	db_print_process(current, db_i);
			if (current->cycle == 0)
			{
				vm_exec_inst(all, current);
				init_pro_cycle(all, current);
			}
			else
				current->cycle--;
			current = current->next;
			db_i++;
		}
		manage_cycle(all);
	}
	vm_del_all_pro(&all->process_list);
}
