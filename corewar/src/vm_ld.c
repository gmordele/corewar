/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:32:35 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:58:25 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Instruction ld et lld.
** Si le paramètre "lld" est à 0 on fait un ld sinon on fait un lld.
** Le 1er paramètre est quelconque donc on utilise le bit d'encodage pour
** l'identifier. Si on fait un ld et que le 1er paramètre est un indirect, alors
** on lui applique un % IDX_MOD.
** Le second paramètre est un registre. On prend la valeur du 1er
** paramètre et on la stock dans le registre. Si le registre est valide et que
** la valeur est 0 alors le carry passe à 1.
*/

#include "vm_0.h"

int		vm_ld(t_all *all, t_process *proc, int type_param[3], int lld)
{
	int param;
	int	reg;

	reg = (type_param[0] == 2) ? proc->pc + 4 : proc->pc + 6;
	if (type_param[0] == 2)
		param = vm_convert_param(all, proc->pc + 1, 2);
	else
	{
		param = vm_convert_param(all, proc->pc + 1, 4);
		if (!lld)
			param = vm_ajust_addr(param % IDX_MOD);
	}
	if (!reg || reg > REG_NUMBER)
		return (0);
	else
		proc->r[reg] = param;
	if (!param)
		proc->carry = 1;
	else
		proc->carry = 0;
	return (1);
}
