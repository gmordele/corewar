/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:35:50 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:37:36 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
** Instruction sub.
** Prend 3 registres en paramètre.
** On soustraie les valeurs des deux premiers registres et on stocke le
** résultat dans le 3ème registre.
** Modifie le carry si l'opération réussi et que la soustraction donne 0.
** L'opération échoue si un des registres n'existe pas.
*/

void	vm_sub(t_all *all, t_process *proc)
{
	int	param1;
	int	param2;
	int	param3;

	param1 = all->arena[proc->pc + 2];
	param2 = all->arena[proc->pc + 3];
	param3 = all->arena[proc->pc + 4];
	proc->r[param3] = proc->r[param1] - proc->r[param2];
	if (!proc->r[param3])
		proc->carry = 1;
	else
		proc->carry = 0;
}
