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

void	vm_ld(t_all *all, t_process *proc)
{
	(void)all;
	(void)proc;
}
