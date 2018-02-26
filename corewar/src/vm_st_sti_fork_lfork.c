/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st_sti_fork_lfork.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:19:30 by edebise           #+#    #+#             */
/*   Updated: 2018/02/23 00:17:25 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_st()
**	write reg value (first arg) in a second reg or in arena (second arg)
**	if the second arg is a IND
**		set IND with % IDX_MOD
**		write process->pc color in all->color[]
**	process->step is increased by (2 + sum of arg_size)
*/

void	vm_st(t_all *all, t_process *pro)
{
	ft_strcpy(pro->op, "st");				//	Debug
//	pf("{y}vm_st\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 3))
	{
		if (pro->decoded[1] & T_REG)
			pro->r[pro->arg[1]] = pro->value[0];
		else
		{
			pro->arg[1] %= IDX_MOD;
			vm_put_mem(all, pro->value[0], pro->pc + pro->arg[1], REG_SIZE);
			vm_put_color(all, pro, pro->pc + pro->arg[1], REG_SIZE);
		}
	}
	else
		ft_strcat(pro->op, " invalide");
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1];
}

/*
**	vm_sti()
**	write reg value (first arg) in arena
**	the address of writing in arena is define by :
**		(sum of second and third params) % IDX_MOD
**	write process->pc color in all->color[]
**	process->step is increased by (2 + sum of arg_size)
*/

void	vm_sti(t_all *all, t_process *pro)
{
	int	address;

	ft_strcpy(pro->op, "sti");				//	Debug
//	pf("{y}vm_sti\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 11))
	{
		address = (pro->value[1] + pro->value[2]) % IDX_MOD;
		vm_put_mem(all, pro->value[0], pro->pc + address, REG_SIZE);
		vm_put_color(all, pro, pro->pc + address, REG_SIZE);
	}
	else
		ft_strcat(pro->op, " invalide");
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

void	vm_fork(t_all *all, t_process *pro)
{
	int			new_pc;

	ft_strcpy(pro->op, "fork");				//	Debug
//	pf("{y}vm_fork\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 12))
	{
//		vm_visu(all);
		new_pc = (pro->pc + (pro->value[0] % IDX_MOD)) % MEM_SIZE;
		vm_add_pro_frt(&all->process_list, vm_new_pro(all, pro, new_pc));
//		vm_visu(all);
	//	init_pro_cycle(all, all->process_list);
	}
	else
		ft_strcat(pro->op, " invalide");
	pro->step += pro->arg_size[0];
}

void	vm_lfork(t_all *all, t_process *pro)
{
	int			new_pc;

	ft_strcpy(pro->op, "lfork");				//	Debug
//	pf("{y}vm_lfork\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 12))
	{
//		vm_visu(all);
		new_pc = (pro->pc + pro->value[0]) % MEM_SIZE;
		vm_add_pro_frt(&all->process_list, vm_new_pro(all, pro, new_pc));
	//	init_pro_cycle(all, all->process_list);
	}
	else
		ft_strcat(pro->op, " invalide");
	pro->step += pro->arg_size[0];
}
