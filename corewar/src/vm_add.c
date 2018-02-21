/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:27:22 by proso             #+#    #+#             */
/*   Updated: 2018/02/21 18:34:08 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_sub(t_all *all, t_process *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)all;
	reg1 = proc->r[proc->arg[0]];
	reg3 = proc->r[proc->arg[1]];
	reg2 = proc->r[proc->arg[2]];
	proc->r[reg3] = reg1 - reg2;
	proc->carry = (reg1 - reg2) ? 0 : 1;
}

void	vm_add(t_all *all, t_process *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)all;
	reg1 = proc->r[proc->arg[0]];
	reg3 = proc->r[proc->arg[1]];
	reg2 = proc->r[proc->arg[2]];
	proc->r[reg3] = reg1 + reg2;
	proc->carry = (reg1 + reg2) ? 0 : 1;
}
