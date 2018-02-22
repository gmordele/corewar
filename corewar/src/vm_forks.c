/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:04:53 by proso             #+#    #+#             */
/*   Updated: 2018/02/22 22:00:52 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_lfork(t_all *all, t_process *proc)
{
	t_process	*new;
	int			new_pc;

	new_pc = vm_get_mem(all, proc->pc + 1, 2);
	new = vm_new_pro(all, proc, (proc->pc + new_pc) % MEM_SIZE);
}

void	vm_fork(t_all *all, t_process *proc)
{
	t_process	*new;
	int			new_pc;

	new_pc = vm_get_mem(all, proc->pc + 1, 2);
	new = vm_new_pro(all, proc, (proc->pc + new_pc) % IDX_MOD);
}
