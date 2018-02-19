/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:38:13 by edebise           #+#    #+#             */
/*   Updated: 2018/02/19 19:38:15 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

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
**			process->step is increased by sum of arg_size
**	otherwise, function quit
*/

int		vm_xor(t_all *all, t_process *pro)
{
	int *reg;

	pf("{y}vm_xor\n{0}");						//	Debug
	if (vm_check_args(all, pro, 6))
	{
		pf("Args valides\n");					//	Debug
		vm_get_value(all, pro);
		if (pro->arg[2] > 0 && pro->arg[2] <= REG_NUMBER)
		{
			reg = pro->r + pro->arg[2];
			*reg = rev_endian_int(pro->value[0] ^ pro->value[1]);
			pro->carry = (*reg ? 0 : 1);
			pro->step = 2 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
			pf("Xor -> %08x\n", *reg);			//	Debug
		}
	}
	return (0);
}
