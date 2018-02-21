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

void	vm_add(t_all *all, t_process *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)all;
	reg1 = proc->r[proc->arg[0]];
	reg3 = proc->r[proc->arg[1]];
	reg2 = proc->r[proc->arg[2]];
	proc->r[reg3] = reg1 + reg2;
	proc->carry = (reg1 + reg2) ? 0 : 1;
}

void	vm_sub(t_all *all, t_process *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)all;
	reg1 = proc->r[proc->arg[0]];
	reg3 = proc->r[proc->arg[1]];
	reg2 = proc->r[proc->arg[2]];
	proc->r[reg3] = reg1 - reg2;
	proc->carry = (reg1 - reg2) ? 0 : 1;
}

/*
**	vm_and()
**	call vm_check_args() which check if 'encoded byte' is valid with op_tab
**	if valid
**		vm_check_args() fill process->arg_size
**		vm_check_args() fill process->arg
**		vm_check_args() fill process->value
**		if process->arg[2] is a valid register
**			register is filled with a '&' result
**			carry could be fixed
**			process->step is increased by sum of arg_size
**	otherwise, function quit
*/

void	vm_and(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_and\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 6))
	{
		pf("Args valides\n");					//	Debug
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] & pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
		pf("And -> %08x\n", *reg);			//	Debug
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_or()
**	call vm_check_args() which check if 'encoded byte' is valid with op_tab
**	if valid
**		vm_check_args() fill process->arg_size
**		vm_check_args() fill process->arg
**		vm_check_args() fill process->value
**		if process->arg[2] is a valid register
**			register is filled with a '|' result
**			carry could be fixed
**			process->step is increased by sum of arg_size
**	otherwise, function quit
*/

void	vm_or(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_or\n{0}");						//	Debug
	if (vm_check_and_get_args(all, pro, 7))
	{
		pf("Args valides\n");					//	Debug
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] | pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
		pf("Or -> %08x\n", *reg);			//	Debug
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}

/*
**	vm_xor()
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
		pf("Args valides\n");					//	Debug
		reg = pro->r + pro->arg[2];
		*reg = rev_endian_int(pro->value[0] ^ pro->value[1]);
		pro->carry = (*reg ? 0 : 1);
		pf("Xor -> %08x\n", *reg);			//	Debug
	}
	pro->step += 1 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}
