/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_5_op_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:01:51 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:52:32 by proso            ###   ########.fr       */
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
**		the address is set with %IDX_MOD
*/

int		vm_get_values(t_all *all, t_process *pro)
{
	int n;

	n = 0;
	while (n < MAX_ARGS_NUMBER && pro->decoded[n])
	{
		if (pro->decoded[n] & T_DIR)
			pro->value[n] = pro->arg[n];
		else if (pro->decoded[n] & T_REG)
		{
			if (pro->arg[n] < 1 || pro->arg[n] > REG_NUMBER)
			{
				visu_print(all, " Bad reg, ");
				return (0);
			}
			pro->value[n] = pro->r[pro->arg[n]];
		}
		else if (pro->decoded[n] & T_IND)
		{
			pro->arg[n] %= IDX_MOD;
			pro->value[n] = vm_get_mem(all, pro->pc + pro->arg[n], 4);
		}
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
		n = 0;
		while (n < MAX_ARGS_NUMBER && tab->args[n])
		{
			if ((process->encoded >> (6 - (2 * n)) & 0x3) == REG_CODE)
				process->decoded[n] = T_REG;
			if ((process->encoded >> (6 - (2 * n)) & 0x3) == DIR_CODE)
				process->decoded[n] = T_DIR;
			if ((process->encoded >> (6 - (2 * n)) & 0x3) == IND_CODE)
				process->decoded[n] = T_IND;
			++n;
		}
	}
	else
		process->decoded[0] = tab->args[0];
}

/*
**	vm_get_arg_size()
**	get size of each arg of decoded_byte[]
*/

void	vm_get_arg_size(t_all *all, t_process *process, t_op *tab)
{
	int			n;

	n = 0;
	visu_print(all, "Arg");
	while (tab->args[n])
	{
		if (process->decoded[n] & T_REG)
		{
			visu_print(all, "_R");
			process->arg_size[n] = 1;
		}
		else if (process->decoded[n] & T_IND)
		{
			visu_print(all, "_I");
			process->arg_size[n] = 2;
		}
		else if (process->decoded[n] & T_DIR)
		{
			visu_print(all, "_D");
			process->arg_size[n] = (tab->index ? 2 : 4);
		}
		n++;
	}
	visu_print(all, "\t");
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
	vm_get_arg_size(all, process, &g_op_tab[op_code - 1]);
	n = 0;
	while (g_op_tab[op_code - 1].args[n])
	{
		if (!(g_op_tab[op_code - 1].args[n] & process->decoded[n]))
		{
			visu_print(all, " Bad encod_byte, ");
			return (0);
		}
		n++;
	}
	vm_get_args(all, process, &g_op_tab[op_code - 1]);
	return (vm_get_values(all, process));
}
