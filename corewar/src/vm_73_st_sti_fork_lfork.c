/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st_sti_fork_lfork.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:19:30 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:31:10 by proso            ###   ########.fr       */
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
	int	address;

	if (vm_check_and_get_args(all, pro, 3))
	{
		if (pro->decoded[1] & T_REG)
		{
			pro->r[pro->arg[1]] = pro->value[0];
			visu_print(all, "st %08x in r%02x\n", pro->value[0], pro->arg[1]);
		}
		else
		{
			address = (pro->pc + (pro->arg[1] % IDX_MOD));
			vm_put_mem(all, pro->value[0], address, REG_SIZE);
			vm_put_color(all, pro, address, REG_SIZE);
			visu_print(all, "st %08x at %04x\n", pro->value[0], address);
		}
	}
	else
		visu_print(all, "can't st !\n");
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

	if (vm_check_and_get_args(all, pro, 11))
	{
		address = (pro->value[1] + pro->value[2]) % IDX_MOD;
		vm_put_mem(all, pro->value[0], pro->pc + address, REG_SIZE);
		vm_put_color(all, pro, pro->pc + address, REG_SIZE);
		visu_print(all, "sti %08x at %04x\n", pro->value[0], address);
	}
	else
		visu_print(all, "can't sti !\n");
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

void	vm_fork(t_all *all, t_process *pro)
{
	int			new_pc;

	if (vm_check_and_get_args(all, pro, 12))
	{
		new_pc = vm_ajust_addr(pro->pc + (pro->value[0] % IDX_MOD));
		vm_add_pro_frt(&all->process_list, vm_new_pro(all, pro, new_pc));
		visu_print(all, "fork to %d\n", new_pc);
	}
	else
		visu_print(all, "can't fork !\n");
	pro->step += pro->arg_size[0];
}

void	vm_lfork(t_all *all, t_process *pro)
{
	int			new_pc;

	if (vm_check_and_get_args(all, pro, 12))
	{
		new_pc = vm_ajust_addr(pro->pc + pro->value[0]);
		vm_add_pro_frt(&all->process_list, vm_new_pro(all, pro, new_pc));
		visu_print(all, "lfork to %d\n", new_pc);
	}
	else
		visu_print(all, "can't lfork !\n");
	pro->step += pro->arg_size[0];
}
