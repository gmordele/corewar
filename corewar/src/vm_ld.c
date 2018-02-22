/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:32:35 by proso             #+#    #+#             */
/*   Updated: 2018/02/21 19:04:26 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*void	vm_lldi(t_all *all, t_process *proc)
{
	int		add;
	int		reg;
	(void)all;

	reg = proc->arg[2];
	add = (proc->value[0] + proc->value[1]) % MEM_SIZE;
	add = vm_get_mem(all, add, 1);
	proc->r[reg] = add;
	proc->step += proc->arg_size[0] + proc->arg_size[1] + proc->arg_size[2];
}

void	vm_ldi(t_all *all, t_process *proc)
{
	int		add;
	int		reg;
	(void)all;

	reg = proc->arg[2];
	add = (proc->value[0] + proc->value[1]) % IDX_MOD;
	add = vm_get_mem(all, add, 1);
	proc->r[reg] = add;
	proc->step += proc->arg_size[0] + proc->arg_size[1] + proc->arg_size[2];
}

void	vm_lld(t_all *all, t_process *proc)
{
	int		value;
	int		reg;

	(void)all;
	value = proc->arg[0];
	reg = proc->arg[1];
	proc->r[reg] = value;
	proc->carry = (value) ? 0 : 1;
	proc->step += proc->arg_size[0] + proc->arg_size[1] + proc->arg_size[2];
}

void	vm_ld(t_all *all, t_process *proc)
{
	int		value;
	int		reg;

	(void)all;
	value = (proc->decoded[0] == T_IND) ? proc->arg[0] % IDX_MOD : proc->arg[0];
	reg = proc->arg[1];
	proc->r[reg] = value;
	proc->carry = (value) ? 0 : 1;
	proc->step += proc->arg_size[0] + proc->arg_size[1] + proc->arg_size[2];
}*/
