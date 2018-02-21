/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:54:14 by edebise           #+#    #+#             */
/*   Updated: 2018/02/21 15:54:16 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

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

	pf("{y}vm_sti\n{0}");						//	Debug
//	ft_bzero(pro->arg_size, sizeof(int) * MAX_ARGS_NUMBER);
	if (vm_check_and_get_args(all, pro, 11))
	{
		pf("{y}Args valides\n{0}");					//	Debug
		address = (pro->value[1] + pro->value[2]) % IDX_MOD;
		vm_put_mem(all, pro->value[0], pro->pc + address, REG_SIZE);
		vm_put_color(all, pro, pro->pc + address, REG_SIZE);
	}
	pro->step = 2 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
}
