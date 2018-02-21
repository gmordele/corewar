/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_4_run_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:59:11 by edebise           #+#    #+#             */
/*   Updated: 2018/02/20 01:01:52 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	
*/

void	vm_run_battle(t_all *all)
{
	t_process	*process;
	int			op;
	char		*gnl;

	while (all->process_list)
	{
		process = all->process_list;
		while (process)
		{
			pf("Process->PC %d\n", process->pc);
			vm_print_arena(all);
			get_next_line(0, &gnl);
			process->step = 1;
			op = vm_get_mem(all, process->pc, 1);
			if (op > 0 && op < 17)
				all->op_fn[op](all, process);
			process->pc = vm_correct_addr(process->pc + process->step);
			process = process->next;
		}
	}
}


/*static void	delete_dead_process(t_all *all)
{
	t_process	*current;
	t_process	*tmp;
	int			nb_live;

	nb_live = 0;
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
			nb_live += current->nb_live;
			current->nb_live = 0;
			current = current->next;
		}
	}
	if (nb_live >= NBR_LIVE)
		all->cycle_to_die -= CYCLE_DELTA;
	else
		all->nb_checks++;
}

static void	manage_cycle(t_all *all)
{
	all->cycle++;
	if (!all->cycle % all->cycle_to_die)
		delete_dead_process(all);
	if (all->nb_checks >= 10)
	{
		all->cycle_to_die -= CYCLE_DELTA;
		all->nb_checks = 0;
	}
	if (all->cycle_to_die < 0)
		all->cycle_to_die = 0;
}

static void	init_pro_cycle(t_all *all, t_process *process)
{
	int	op;

	
}

void	vm_run_battle(t_all *all)
{
	t_process	*current;

	while (all->cycle_to_die && all->process_list)
	{
		current = all->process_list;
		while (current)
		{
			if (current->cycle == 0)
			{
				vm_exec_inst(all, current);
				init_pro_cycle(all, current);
			}
			else
				current->cycle--;
			current = current->next;
		}
		manage_cycle(all);
	}
	vm_del_all_pro(&all->process_list);
}*/
