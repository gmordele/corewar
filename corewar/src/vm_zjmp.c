/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:20:13 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:57:35 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
** Instruction zjmp.
** Le PC actuel prend la valeur du 1er (et seul) paramètre.
** Cette instruction ne fonctionne que si le carry est à 1.
*/

int		vm_zjmp(t_all *all, t_process *proc)
{
	if (proc->carry)
	{
		proc->pc = vm_ajust_addr(all->arena[proc->pc + 1]);
		return (1);
	}
	return (0);
}
