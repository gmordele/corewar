/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld_lld_ldi_lldi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:28:17 by edebise           #+#    #+#             */
/*   Updated: 2018/02/22 22:30:50 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_ld()		code:2
**	load an int value in the register define by the first param
**	if params are valids
**		if the second param is an IND
**			the value will be find in the arena
**			the address is define by the IND % IDX_MOD
**		if the second param is a direct
**			the value is the direct value
**		process->carry could be fixed
**	process->step is increased by sum of arg_size
*/

void	vm_ld(t_all *all, t_process *pro)
{
	int	address;

	ft_strcpy(pro->op, "ld");			//	Debug
	if (vm_check_and_get_args(all, pro, 2))
	{
		if (pro->decoded[0] & T_IND)
		{
			address = pro->pc + (pro->arg[0] % IDX_MOD);
			pro->value[0] = vm_get_mem(all, address, 4);
		}
		pro->r[pro->arg[1]] = pro->value[0];
		pro->carry = (pro->r[pro->arg[1]] ? 0 : 1);
		visu_print(all, "ld %08x in r%02x\n", pro->value[0], pro->arg[1]);
	}
	else
	{
		visu_print(all, "can't ld !\n");
		ft_strcat(pro->op, " invalide");
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1];
}

/*
**	vm_lld()		code:13
**	load an int value in the register define by the first param
**	if params are valids
**		if the second param is an IND
**			the value will be find in the arena
**			the address is define by the IND % IDX_MOD
**		if the second param is a direct
**			the value is the direct value
**		process->carry could be fixed
**	process->step is increased by sum of arg_size
*/

void	vm_lld(t_all *all, t_process *pro)		//	A modifier, le lld de zaz ne prend
{
	int	address;

	ft_strcpy(pro->op, "lld");				//	Debug
	if (vm_check_and_get_args(all, pro, 13))
	{
		if (pro->decoded[0] & T_IND)
		{
			address = pro->pc + pro->arg[0];
			pro->value[0] = vm_get_mem(all, address, 2);
			//pro->value[0] = vm_get_mem(all, address, 4);
		}
		pro->r[pro->arg[1]] = pro->value[0];
		pro->carry = (pro->r[pro->arg[1]] ? 0 : 1);
		visu_print(all, "lld %08x in r%02x\n", pro->value[0], pro->arg[1]);
	}
	else
	{
		visu_print(all, "can't lld !\n");
		ft_strcat(pro->op, " invalide");
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1];
}

/*
**	vm_ldi()		code:10
**	load an int value in the register define by the third param
**	if params are valids
**		add first and second param value
**		this value is treated as an address
**		the value of the register will be find at this address % IDX_MOD
**	process->step is increased by sum of arg_size
*/

void	vm_ldi(t_all *all, t_process *pro)
{
	int	address;

			ft_strcpy(pro->op, "ldi");				//	Debug
	if (vm_check_and_get_args(all, pro, 10))
	{
		address = pro->pc + ((pro->value[0] + pro->value[1]) % IDX_MOD);
		address = vm_ajust_addr(address);
		pro->r[pro->arg[2]] = vm_get_mem(all, address, 4);
		visu_print(all, "ldi %08x (from %04x) ", pro->r[pro->arg[2]], address);
		visu_print(all, "in r%02x\n", pro->arg[2]);
	}
	else
	{
		visu_print(all, "can't ldi !\n");
		ft_strcat(pro->op, " invalide");
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_lldi()		code:14
**	load an int value in the register define by the third param
**	if params are valids
**		add first and second param value
**		this value is treated as an address
**		the value of the register will be find at this address
**		process->carry could be fixed
**	process->step is increased by sum of arg_size
*/

void	vm_lldi(t_all *all, t_process *pro)
{
	int	address;

			ft_strcpy(pro->op, "lldi");				//	Debug
	if (vm_check_and_get_args(all, pro, 14))
	{
		address = vm_ajust_addr(pro->pc + pro->value[0] + pro->value[1]);
		pro->r[pro->arg[2]] = vm_get_mem(all, address, 4);
		pro->carry = (pro->r[pro->arg[2]] ? 0 : 1);
		visu_print(all, "lldi %08x (from %04x) ", pro->r[pro->arg[2]], address);
		visu_print(all, "in r%02x\n", pro->arg[2]);
	}
	else
	{
		visu_print(all, "can't lldi !\n");
		ft_strcat(pro->op, " invalide");
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}
