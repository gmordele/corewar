/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:34:43 by proso             #+#    #+#             */
/*   Updated: 2018/02/21 19:31:40 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*static void vm_get_type_param(t_all *all, t_process *proc, int type_param[3])
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
}*/

void		db_print_process(t_process *proc, int num)
{
	pf("{c}Process %d{0}\n", num);
	pf("PC : [{g}%d{0}]\nCarry : [{g}%d{0}]\nCycle : [{g}%d{0}]\n", proc->pc, proc->carry, proc->cycle);
	if (proc->nb_live)
		pf("Nb live : [{g}%d{0}]\n", proc->nb_live);
	else
		pf("Nb live : [{r}%d{0}]\n", proc->nb_live);
}

void		vm_exec_inst(t_all *all, t_process *proc)
{
	char	*gnl;
	int		op;

	proc->step = 1;
	op = vm_get_mem(all, proc->pc, 1);
	if (op > 0 && op < 17)
	{
		get_next_line(0, &gnl);			//	Debug
		all->op_fn[op](all, proc);
		pf("process->pc : %d\n", proc->pc);
		vm_print_arena(all, proc);			//	Debug
//		sleep(3);
	}
	proc->pc = vm_correct_addr(proc->pc + proc->step);
}
