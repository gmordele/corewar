/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live_zjmp_aff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:37:20 by edebise           #+#    #+#             */
/*   Updated: 2018/02/21 20:37:24 by edebise          ###   ########.fr       */
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
	process->step += DIR_SIZE;
	process->nb_live++;
	all->nb_live++;
	n = all->nb_champ;
	while (n-- > 0)
		if (process->value[0] == all->champ[n].nb && pf("{y}live from {r}%s\n{0}", all->champ[n].header.prog_name))
			all->last_live = n;
}

/*
** Instruction zjmp.
** Le PC actuel prend la valeur du 1er (et seul) paramètre.
** Cette instruction ne fonctionne que si le carry est à 1.
*/

void	vm_zjmp(t_all *all, t_process *proc)
{
	if (vm_check_and_get_args(all, proc, 9) && proc->carry)
	{
		proc->pc = vm_get_mem(all, proc->pc + 1, 2) % MEM_SIZE;
		proc->step = 0;
	}
	else
		proc->step += proc->arg_size[0];
}

void	vm_aff(t_all *all, t_process *process)
{
	char *str;

	pf("{y}vm_aff\n{0}");
	if (vm_check_and_get_args(all, process, 16))
	{
		str = (char*)vm_malloc(all, all->aff_str_size + 1);
		ft_memcpy(str, all->aff_str, all->aff_str_size);
		str[all->aff_str_size] = process->value[0] % 256;
		ft_free(1, &all->aff_str);
		all->aff_str = str;
		write(1, all->aff_str, ++all->aff_str_size);
	}
	process->step += 1 + process->arg_size[0];
}
