/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_test_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:00:22 by edebise           #+#    #+#             */
/*   Updated: 2018/02/23 17:00:23 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_clean_process_list(t_all *all)
{
	t_process *process;
	t_process *tmp;

	process = all->process_list;
	while (process)
	{
		if (!process->nb_live)
		{
			pf("kill process %d at %d cycles\n", process->nb, all->cycle);
			tmp = process;
			process = process->next;
			vm_del_one_pro(&all->process_list, tmp);
		}
		else
		{
			process->nb_live = 0;
			process = process->next;
		}
	}
}

void	vm_update_process(t_all *all, t_process *process)
{
	extern t_op	g_op_tab[];
	int			op;

	process->pc = vm_correct_addr(process->pc + process->step);
	process->step = 1;
	if ((op = vm_get_mem(all, process->pc, 1)) > 0 && op <= REG_NUMBER)
		process->cycle = g_op_tab[op - 1].cycles;
}

void	vm_run_battle(t_all *all)
{
	t_process	*process;
	int			op;

	all->cycle_to_die = CYCLE_TO_DIE;
	while ((process = all->process_list) && all->cycle_to_die > 0)
	{
		while (process)
		{
			if (process->cycle < 0)
				vm_update_process(all, process);
			if (!process->cycle && (op = vm_get_mem(all, process->pc, 1)) > 0 && op <= REG_NUMBER)
			{
				all->op_fn[op](all, process);
				get_next_line(0, &all->gnl);				//	Debug
				vm_print_arena(all, process);			//	Debug
			}
		//	get_next_line(0, &all->gnl);				//	Debug
		//	vm_print_arena(all, process);			//	Debug
			--process->cycle;
			process = process->next;
		}
		++all->cycle;
		if (--all->cycle_to_die < 1)
		{
			vm_clean_process_list(all);
			all->cycle_to_die = CYCLE_TO_DIE;
			if (all->nb_live >= NBR_LIVE || ++all->nb_checks > MAX_CHECKS)
			{
				all->nb_checks = 0;
				all->cycle_delta += CYCLE_DELTA;
				all->cycle_to_die -= all->cycle_delta;
			}
		}
	}
}
