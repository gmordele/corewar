/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_4_run_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:59:11 by edebise           #+#    #+#             */
/*   Updated: 2018/02/19 18:59:13 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_run_battle(t_all *all)
{
	t_process	*process;
	int			op;
//	char		*gnl;

	while (all->process_list)
	{
		process = all->process_list;
		while (process)
		{
			pf("Process->PC %d\n", process->pc);
			vm_print_arena(all);
//			get_next_line(0, &gnl);
			process->step = 1;
			op = vm_get_mem(all, process->pc, 1);
			if (op > 0 && op < 17)
				all->op_fn[op](all, process);
			process->pc = vm_correct_addr(process->pc + process->step);
			process = process->next;
		}
	}
}
