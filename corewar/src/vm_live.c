/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:45:18 by edebise           #+#    #+#             */
/*   Updated: 2018/02/20 12:45:22 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_live()
**	increase process->nb_live by 1
**	if process->value[0] is a real all->champ[].nb
**		define all->last_live at n (all->champ[n])
**	process->step is increased by 1 + DIR_SIZE (so 5)
*/

void	vm_live(t_all *all, t_process *process)
{
	int	n;

	pf("{y}vm_live\n{0}");						//	Debug
//	ft_bzero(process->value, sizeof(int) * MAX_ARGS_NUMBER);
	process->value[0] = vm_get_mem(all, process->pc + 1, 4);
	process->step = 1 + DIR_SIZE;
	process->nb_live++;
	all->nb_live++;
	n = all->nb_champ;
	while (n-- > 0)
		if (process->value[0] == all->champ[n].nb && pf("{y}live from {r}%s\n{0}", all->champ[n].header.prog_name))
			all->last_live = n;
}
