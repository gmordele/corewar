/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_test_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:00:22 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:37:13 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void		vm_clean_process_list(t_all *all)
{
	t_process *process;
	t_process *tmp;

	process = all->process_list;
	while (process)
	{
		if (!process->nb_live)
		{
			visu_print(all, "R.I.P.: Process_%d\n", process->nb);
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

void		vm_update_process(t_all *all, t_process *process)
{
	extern t_op	g_op_tab[];

	process->pc = vm_ajust_addr(process->pc + process->step);
	process->step = 1;
	process->op = vm_get_mem(all, process->pc, 1);
	if (process->op > 0 && process->op <= 16)
		process->cycle = g_op_tab[process->op - 1].cycles - 1;
}

static void	manage_cycle(t_all *all)
{
	vm_clean_process_list(all);
	if (all->nb_live >= NBR_LIVE || ++all->nb_checks >= MAX_CHECKS)
	{
		all->cycle_delta += CYCLE_DELTA;
		all->nb_checks = 0;
	}
	all->cycle_to_die = CYCLE_TO_DIE - all->cycle_delta;
	all->nb_live = 0;
	if (!all->process_list && all->flag & VISU)
	{
		all->pause = 1;
		all->aff_str_size ? visu_print(all, "\nAff:%.*s\n",
			all->aff_str_size, all->aff_str) : 0;
		visu_print(all, "\n########## THE WINNER IS \"%s\" ##########",
			all->champ[all->last_live].header.prog_name);
	}
}

void		vm_run_battle(t_all *all)
{
	t_process	*process;

	if (all->flag & VISU)
		vm_visu(all);
	while ((process = all->process_list) && all->cycle_to_die > 0
		&& all->cycle < all->dump)
	{
		++all->cycle;
		while (process)
		{
			if (--process->cycle < 0)
				vm_update_process(all, process);
			if (!process->cycle && process->op > 0 && process->op <= 16)
			{
				visu_print(all, "Process_%d: ", process->nb);
				all->op_fn[process->op](all, process);
			}
			process = process->next;
		}
		if (--all->cycle_to_die <= 0)
			manage_cycle(all);
		if (all->flag & VISU)
			vm_visu(all);
	}
}
