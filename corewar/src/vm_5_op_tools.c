/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_5_op_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:01:51 by edebise           #+#    #+#             */
/*   Updated: 2018/02/19 16:01:53 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_get_value()
**	get value of each arg of process->arg[]
**	each value is stored in process->value[]
**	if decode[n] is a T_REG
**		value[n] is set with the reg value
**	if decoded[n] is a T_DIR
**		value[n] is set with the arg[n]
**	if decoded[n] is a T_IND
**		value is set with 4 bytes from arena
*/

int		vm_get_values(t_all *all, t_process *process)
{
	int n;

//	pf("Get values\n");
	n = 0;
	while (n < MAX_ARGS_NUMBER && process->decoded[n])
	{
		if (process->decoded[n] & T_DIR)
			process->value[n] = process->arg[n];
		else if (process->decoded[n] & T_REG)
		{
			if (process->arg[n] < 1 || process->arg[n] > REG_NUMBER)
				return (0);
			process->value[n] = process->r[process->arg[n]];
		}
		else if (process->decoded[n] & T_IND)
			process->value[n] = vm_get_mem(all, process->pc + process->arg[n], 4);
		n++;
	}
	return (1);
}

/*
**	vm_get_args()
**	get each arg of instruction in process->arg[]
*/

void	vm_get_args(t_all *all, t_process *process, t_op *tab)
{
	int			virtual_pc;
	int			n;

	virtual_pc = process->pc + (tab->encod_byte ? 2 : 1);
	n = 0;
	while (n < MAX_ARGS_NUMBER && process->arg_size[n])
	{
		process->arg[n] = vm_get_mem(all, virtual_pc, process->arg_size[n]);
		virtual_pc += process->arg_size[n];
		n++;
	}
}

/*
**	vm_decode_byte()
**	get the encoded byte in arena at pc + 1
**	split encoded arg_type in process->decoded[]
*/

void	vm_decode_byte(t_all *all, t_process *process, t_op *tab)
{
	int			n;

	if (tab->encod_byte)
	{
		process->encoded = vm_get_mem(all, process->pc + 1, 1);
		n = MAX_ARGS_NUMBER;
		while (n-- > 0)
		{
			if ((process->encoded & 0x3) == REG_CODE)
				process->decoded[n] = T_REG;
			else if ((process->encoded & 0x3) == DIR_CODE)
				process->decoded[n] = T_DIR;
			else if ((process->encoded & 0x3) == IND_CODE)
				process->decoded[n] = T_IND;
			process->encoded >>= 2;
		}
	}
	else
		process->decoded[0] = tab->args[0];
}

/*
**	vm_get_arg_size()
**	get size of each arg of decoded_byte[]
*/

void	vm_get_arg_size(t_process *process, t_op *tab)
{
	int			n;

	n = 0;
	while (tab->args[n])
	{
		if (process->decoded[n] & T_REG)
			process->arg_size[n] = 1;
		else if (process->decoded[n] & T_IND)
			process->arg_size[n] = 2;
		else if (process->decoded[n] & T_DIR)
			process->arg_size[n] = (tab->index ? 2 : 4);
		n++;
	}
}

/*
**	vm_check_args()
**	call vm_decode_byte() first
**	then call vm_get_arg_size()
**	then compare process->decoded[n] with g_op_tab->args_type
**	if valid
**		get value of each arg in process->arg_value[]
**	otherwise
**		return (0)
*/

int		vm_check_and_get_args(t_all *all, t_process *process, int op_code)
{
	extern t_op	g_op_tab[];
	int			n;

	ft_bzero(process->decoded, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(process->arg_size, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(process->arg, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(process->value, sizeof(int) * MAX_ARGS_NUMBER);
	vm_decode_byte(all, process, &g_op_tab[op_code - 1]);
	vm_get_arg_size(process, &g_op_tab[op_code - 1]);
	n = 0;
	while (g_op_tab[op_code - 1].args[n])
	{
		if (!(g_op_tab[op_code - 1].args[n] & process->decoded[n]))
			return (0);
		n++;
	}
	vm_get_args(all, process, &g_op_tab[op_code - 1]);
	return (vm_get_values(all, process));
}
