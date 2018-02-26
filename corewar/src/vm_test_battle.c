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
			tmp = process;
			process = process->next;
			vm_del_one_pro(&all->process_list, tmp);
			--all->nb_process;
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

	process->pc = vm_ajust_addr(process->pc + process->step);
	process->step = 1;
	if ((op = vm_get_mem(all, process->pc, 1)) > 0 && op <= 16)
	{
		ft_strcat(process->op, "->");						//	Debug
		ft_strcat(process->op, g_op_tab[op - 1].name);		//	Debug
		process->cycle = g_op_tab[op - 1].cycles - 1;
	}
}

void	vm_run_battle(t_all *all)
{
	t_process	*process;
	int			op;

	all->cycle_to_die = CYCLE_TO_DIE;
	while ((process = all->process_list) && all->cycle_to_die > 0 && all->cycle < all->dump)
	{
		if (all->flag & VISU && all->cycle > 3000)
			vm_visu(all);
		++all->cycle;
		while (process)
		{
			--process->cycle;
			if (process->cycle < 0)
				vm_update_process(all, process);
			if (!process->cycle && (op = vm_get_mem(all, process->pc, 1)) > 0 && op <= 16)
				all->op_fn[op](all, process);
			process = process->next;
		}
		if (--all->cycle_to_die <= 0)
		{
			vm_clean_process_list(all);
			if (all->nb_live >= NBR_LIVE || ++all->nb_checks > MAX_CHECKS)
			{
				all->cycle_delta += CYCLE_DELTA;
				all->nb_checks = 0;
			}
			all->cycle_to_die = CYCLE_TO_DIE - all->cycle_delta;
			all->nb_live = 0;
		}
	}
//	(!all->flag) ? vm_print_arena(all, NULL) : 0;	//	Debug
}
