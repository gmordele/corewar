/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:45:34 by edebise           #+#    #+#             */
/*   Updated: 2018/02/20 12:45:37 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_st()
**	write reg value (first arg) in a second reg or in arena (second arg)
**	if the second arg is a IND
**		write process->pc color in all->color[]
**	process->step is increased by 2 + sum of arg_size
*/

int		vm_st(t_all *all, t_process *pro)
{
	pf("{y}vm_st\n{0}");						//	Debug
//	ft_bzero(pro->arg_size, sizeof(int) * MAX_ARGS_NUMBER);
	if (vm_check_and_get_args(all, pro, 3) && pro->arg[0] > 0
		&& pro->arg[0] <= REG_NUMBER && (pro->decoded[1] & T_IND
		|| (pro->arg[1] > 0 && pro->arg[1] <= REG_NUMBER)))
	{
		pf("Args valides\n");					//	Debug
		if (pro->decoded[1] & T_REG)
			pro->r[pro->arg[1]] = pro->value[0];
		else
		{
			vm_put_mem(all, pro->value[0], pro->pc + pro->arg[1], REG_SIZE);
			vm_put_color(all, pro, pro->pc + pro->arg[1], REG_SIZE);
		}
	}
	pro->step = 2 + pro->arg_size[0] + pro->arg_size[1] + pro->arg_size[2];
	return (0);
}
