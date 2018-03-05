/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live_zjmp_aff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:37:20 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:30:22 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_live()		code:1
**	increase process->nb_live by 1
**	if process->value[0] is a real all->champ[].nb
**		define all->last_live at n (all->champ[n])
**	process->step is increased by 1 + DIR_SIZE (so 5)
*/

void	vm_live(t_all *all, t_process *process)
{
	int	n;

	if (vm_check_and_get_args(all, process, 1))
	{
		++process->nb_live;
		++all->nb_live;
		visu_print(all, "made a live");
		n = all->nb_champ;
		while (n-- > 0)
			if (process->value[0] == all->champ[n].nb)
			{
				all->last_live = n;
				visu_print(all, " from %08x", process->value[0]);
			}
		visu_print(all, "\n");
	}
	else
		visu_print(all, "can't live !\n");
	process->step += process->arg_size[0];
}

/*
**	vm_zjmp()		code:9
**	the process pc jump to the address in the only one param
**	zjmp works only if the carry is not null
*/

void	vm_zjmp(t_all *all, t_process *pro)
{
	if (vm_check_and_get_args(all, pro, 9) && pro->carry)
	{
		pro->pc = vm_ajust_addr(pro->pc + (pro->arg[0] % IDX_MOD));
		pro->step = 0;
		visu_print(all, "zjmp to %04x\n", pro->pc);
	}
	else
	{
		visu_print(all, "can't zjmp !\n");
		pro->step += pro->arg_size[0];
	}
}

/*
**	vm_aff()		code:16
**	print a char
**	this char is define by a register in the only one param
*/

void	vm_aff(t_all *all, t_process *process)
{
	char *str;

	if (vm_check_and_get_args(all, process, 16))
	{
		all->aff_str_size += 1;
		str = (char*)vm_malloc(all, all->aff_str_size + 1);
		all->aff_str ? ft_strcpy(str, all->aff_str) : 0;
		ft_strncat(str, (char*)process->value, 1);
		ft_free(1, &all->aff_str);
		all->aff_str = str;
		visu_print(all, "aff: %s\n", all->aff_str);
	}
	else
		visu_print(all, "can't aff !\n");
	process->step += 1 + process->arg_size[0];
}
