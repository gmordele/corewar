/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_add_sub_and_or_xor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:29:43 by edebise           #+#    #+#             */
/*   Updated: 2018/02/21 20:29:45 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_add()	code:4
*/

void	vm_add(t_all *all, t_process *pro)
{
	pf("{y}vm_add\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 4))
	{
		pro->r[pro->arg[2]] = pro->value[0] + pro->value[1];
		pro->carry = (pro->r[pro->arg[2]] ? 0 : 1);
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_sub()	code:5
*/

void	vm_sub(t_all *all, t_process *pro)
{
	pf("{y}vm_sub\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 5))
	{
		pro->r[pro->arg[2]] = pro->value[0] - pro->value[1];
		pro->carry = (pro->r[pro->arg[2]] ? 0 : 1);
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_and()	code:6
**	call vm_check_args() which check if 'encoded byte' is valid with op_tab
**	if valid
**		vm_check_args() fill process->arg_size
**		vm_check_args() fill process->arg
**		vm_check_args() fill process->value
**		if process->arg[2] is a valid register
**			register is filled with a '&' result
**			carry could be fixed
**	process->step is increased by sum of arg_size
**	otherwise, function quit
*/

void	vm_and(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_and\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 6))
	{
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] & pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_or()		code:7
**	call vm_check_args() which check if 'encoded byte' is valid with op_tab
**	if valid
**		vm_check_args() fill process->arg_size
**		vm_check_args() fill process->arg
**		vm_check_args() fill process->value
**		if process->arg[2] is a valid register
**			register is filled with a '|' result
**			carry could be fixed
**	process->step is increased by sum of arg_size
**	otherwise, function quit
*/

void	vm_or(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_or\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 7))
	{
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] | pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_xor()	code:8
**	call vm_check_args() which check if 'encoded byte' is valid with op_tab
**	if valid
**		vm_check_args() fill process->arg_size
**		vm_check_args() fill process->arg
**		vm_check_args() fill process->value
**		if process->arg[2] is a valid register
**			register is filled with a '^' result
**			carry could be fixed
**	process->step is increased by sum of arg_size
**	otherwise, function quit
*/

void	vm_xor(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_xor\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 8))
	{
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] ^ pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}
