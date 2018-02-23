/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live_zjmp_aff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:37:20 by edebise           #+#    #+#             */
/*   Updated: 2018/02/22 22:31:03 by proso            ###   ########.fr       */
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

	ft_strcpy(process->op, "vm_live");			//	Debug
//	pf("{y}vm_live\n{0}");						//	Debug
	if (vm_check_and_get_args(all, process, 1))
	{
		process->nb_live++;
		all->nb_live++;
		n = all->nb_champ;
		while (n-- > 0)
			if (process->value[0] == all->champ[n].nb)
				all->last_live = n + 1;
	}
	else
		ft_strcat(process->op, " non valide");
	process->step += process->arg_size[0];
}

/*
**	vm_zjmp()		code:9
**	the process pc jump to the address in the only one param
**	zjmp works only if the carry is not null
*/

void	vm_zjmp(t_all *all, t_process *pro)
{
	ft_strcpy(pro->op, "vm_zjmp");			//	Debug
	if (vm_check_and_get_args(all, pro, 9) && pro->carry)
	{
		pro->pc = (pro->pc + pro->arg[0]) % MEM_SIZE;
		pro->step = 0;
	}
	else
	{
		ft_strcat(pro->op, " non valide");
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

	ft_strcpy(process->op, "vm_aff");			//	Debug
//	pf("{y}vm_aff\n{0}");
	if (vm_check_and_get_args(all, process, 16))
	{
		str = (char*)vm_malloc(all, all->aff_str_size + 1);
		ft_memcpy(str, all->aff_str, all->aff_str_size);
		str[all->aff_str_size] = process->value[0] % 256;
		ft_free(1, &all->aff_str);
		all->aff_str = str;
		write(1, all->aff_str, ++all->aff_str_size);
	}
	else
		ft_strcat(process->op, " non valide");
	process->step += 1 + process->arg_size[0];
}
