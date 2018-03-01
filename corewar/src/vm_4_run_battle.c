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
	int			nb_champ;

	process->pc = vm_ajust_addr(process->pc + process->step);
	process->step = 1;
	if ((process->op = vm_get_mem(all, process->pc, 1)) > 0
														&& process->op <= 16)
	{
		nb_champ = all->color[vm_ajust_addr(process->pc)];
		visu_print(all, "Process_%d: (%.3s): ", process->nb,
										all->champ[nb_champ].header.prog_name);
		visu_print(all, "%s in %d cycles\n", g_op_tab[process->op - 1].name,
											g_op_tab[process->op - 1].cycles);
		process->cycle = g_op_tab[process->op - 1].cycles - 1;
	}
}

static void	manage_cycle(t_all *all)
{
	if (--all->cycle_to_die <= 0)
	{
		vm_clean_process_list(all);
		if (all->nb_live >= NBR_LIVE || ++all->nb_checks >= MAX_CHECKS)
		{
			all->cycle_delta += CYCLE_DELTA;
			all->nb_checks = 0;
		}
		all->cycle_to_die = CYCLE_TO_DIE - all->cycle_delta;
	//	vm_visu(all);
		all->nb_live = 0;
	}
}

void		vm_run_battle(t_all *all)
{
	t_process	*process;

	all->cycle_to_die = CYCLE_TO_DIE;
	while ((process = all->process_list) && all->cycle_to_die > 0
		&& all->cycle < all->dump)
	{
		if (all->flag & VISU)// && all->cycle >= 39000)
			vm_visu(all);
		++all->cycle;
		while (process)
		{
			--process->cycle;
			if (process->cycle < 0)
				vm_update_process(all, process);
			if (!process->cycle && process->op > 0 && process->op <= 16)
			{
				visu_print(all, "Process_%d: ", process->nb);
				all->op_fn[process->op](all, process);
			}
			process = process->next;
		}
		manage_cycle(all);
	}
}
