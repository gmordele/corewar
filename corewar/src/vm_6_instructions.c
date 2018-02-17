/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_6_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:34:43 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:55:17 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

static void vm_get_type_param(t_all *all, t_process *proc, int type_param[3])
{
	char	*byte_code;
	int		i;
	int		j;
	int		k;

	ft_bzero(type_param, 3 * sizeof(int));
	byte_code = ft_utoa_base(all->arena[proc->pc + 1], 2, NULL);
	ft_int(0, 2, &i, &k);
	j = 1;
	while (byte_code[i] || byte_code[j])
	{
		if (!byte_code[i] && byte_code[j])
			type_param[k] = 1;
		else if (byte_code[i] && !byte_code[j])
			type_param[k] = 2;
		else
			type_param[k] = 4;
		k++;
		i += 2;
		j += 2;
	}
	ft_strdel(&byte_code);
}

/*static int	vm_choice_inst2(t_all *all, t_process *proc, int type_param[3])
{
	if (proc->pc == 16)
		return (vm_aff(all, proc, type_param));
	else if (proc->pc == 1)
		return (vm_live(all, proc));
	else if (proc->pc == 8)
		return (vm_xor(all, proc, type_param));
	else if (proc->pc == 14)
		return (vm_lldi(all, proc, type_param));
	else if (proc->pc == 6)
		return (vm_and(all, proc, type_param));
	else
		return (-1);
}*/

static int	vm_choice_inst1(t_all *all, t_process *proc, int type_param[3])
{
	if (proc->pc == 15)
		return (vm_fork(all, proc, 1));
	/*else if (proc->pc == 11)
		return (vm_sti(all, proc, type_param));*/
	else if (proc->pc == 12)
		return (vm_fork(all, proc, 0));
	else if (proc->pc == 13)
		return (vm_ld(all, proc, type_param, 1));
	else if (proc->pc == 2)
		return (vm_ld(all, proc, type_param, 0));
	else if (proc->pc == 4)
		return (vm_add(all, proc));
	else if (proc->pc == 9)
		return (vm_zjmp(all, proc));
	else if (proc->pc == 5)
		return (vm_sub(all, proc));
	/*else if (proc->pc == 10)
		return (vm_ldi(all, proc, type_param));
	else if (proc->pc == 7)
		return (vm_or(all, proc, type_param));
	else if (proc->pc == 3)
		return (vm_st(all, proc, type_param));
	else
		return (vm_choice_inst2(all, proc, type_param));*/
	return (1);
}

int			vm_exec_inst(t_all *all, t_process *proc)
{
	int		type_param[3];

	if (proc->pc != 15 && proc->pc != 12 && proc->pc != 9 && proc->pc != 1)
			vm_get_type_param(all, proc, type_param);
	return (vm_choice_inst1(all, proc, type_param));
}
