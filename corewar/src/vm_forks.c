/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:04:53 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:57:07 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
** Instruction fork et lfork.
** Ici si l'int "lfork" vaut 0 on va excuter un fork sinon un lfork.
** On créer un nouveau processus qui hérite de tout les paramètres de son père
** sauf le PC et le num. Le num est celui le plus élevé parmis tout les process
** +1. Le PC devient PC + (1er parametre % IDX_MOD) si c'est un fork ou alors
** PC + 1er parametre si c'est un lfork.
*/

int		vm_fork(t_all *all, t_process *proc, int lfork)
{
	int			param;
	t_process	*new;

	param = all->arena[proc->pc + 1];
	new = (t_process*)vm_malloc(all, sizeof(t_process));
	if (lfork)
		new->pc = vm_ajust_addr(proc->pc + param);
	else
		new->pc = vm_ajust_addr(proc->pc + (param % IDX_MOD));
	new->carry = proc->carry;
	new->nb_live = proc->nb_live;
	new->cycle = proc->cycle;
	new->num = all->process_list->num++;
	ft_memcpy(&new->r[1], &proc->r[1], sizeof(char) * REG_NUMBER);
	vm_add_pro_frt(&all->process_list, new);
	return (1);
}
