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
**	vm_get_args()
**	get each arg of instruction in process->arg[]
*/

void	vm_get_args(t_all *all, t_process *process)
{
	int virtual_pc;
	int n;

//	pf("Get args\n");
	ft_bzero(process->arg, sizeof(int) * MAX_ARGS_NUMBER);
	virtual_pc = process->pc + 2;
	n = 0;
	while (n < MAX_ARGS_NUMBER && process->arg_size[n])
	{
		process->arg[n] = vm_get_mem(all, virtual_pc, process->arg_size[n]);
		virtual_pc += process->arg_size[n];
		n++;
	}
	n = -1;							
	while (++n < 3)
		pf("Prm %d %s, size %d, arg %d\n", n, (process->decoded[n] == T_REG ? "T_REG" : (process->decoded[n] == T_DIR ? "T_DIR" : (process->decoded[n] ? "T_IND" : ""))), process->arg_size[n], process->arg[n]);
}

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

void	vm_get_value(t_all *all, t_process *process)
{
	int n;

//	pf("Get values\n");
	vm_get_args(all, process);
	ft_bzero(process->value, sizeof(int) * MAX_ARGS_NUMBER);
	n = 0;
	while (n < MAX_ARGS_NUMBER && process->decoded[n])
	{
		if (process->decoded[n] & T_DIR)
			process->value[n] = process->arg[n];
		else if (process->decoded[n] & T_REG
			&& process->arg[n] > 0 && process->arg[n] <= REG_NUMBER)
			process->value[n] = process->r[process->arg[n]];
		else if (process->decoded[n] & T_IND)
			process->value[n] = vm_get_mem(all, process->pc + process->arg[n], 4);
		n++;
	}
	n = -1;									//	Debug
	while (++n < 3)							//	Debug
		pf("Prm %d %s, size %d, arg %d, value %08x\n", n, (process->decoded[n] == T_REG ? "T_REG" : (process->decoded[n] == T_DIR ? "T_DIR" : (process->decoded[n] ? "T_IND" : ""))), process->arg_size[n], process->arg[n], process->value[n]);
}

/*
**	vm_decode_byte()
**	get the encoded byte in arena at pc + 1
**	split encoded arg_type in process->decoded[]
*/

void	vm_decode_byte(t_all *all, t_process *process)
{
	int n;

//	pf("Decode byte\n");
	process->encoded = vm_get_mem(all, process->pc + 1, 1);
	ft_bzero(process->decoded, sizeof(int) * MAX_ARGS_NUMBER);
	n = MAX_ARGS_NUMBER;
	while (n-- > 0)
	{
//		pf("Encoded %# hhb\n", process->encoded);
		if ((process->encoded & 0x3) == REG_CODE)
			process->decoded[n] = T_REG;
		else if ((process->encoded & 0x3) == DIR_CODE)
			process->decoded[n] = T_DIR;
		else if ((process->encoded & 0x3) == IND_CODE)
			process->decoded[n] = T_IND;
		process->encoded >>= 2;
	}
	n = -1;
	while (++n < 3)
		pf("Prm %d %s\n", n, (process->decoded[n] == T_REG ? "T_REG" : (process->decoded[n] == T_DIR ? "T_DIR" : (process->decoded[n] ? "T_IND" : ""))));
}

/*
**	vm_check_args()
**	call vm_decode_byte first
**	then compare process->decoded[n] with g_op_tab->args_type
**	if valid
**		define size of each arg in process->arg_size[]
**	otherwise
**		return (0)
*/

int		vm_check_args(t_all *all, t_process *process, int op_code)
{
	extern t_op	g_op_tab[];
	int			n;

//	pf("Check args\n");
	vm_decode_byte(all, process);
	ft_bzero(process->arg_size, sizeof(int) * MAX_ARGS_NUMBER);
	if (op_code > 0 && op_code < 17)
	{
		n = 0;
		while (g_op_tab[op_code - 1].args[n])
		{
			if (!(g_op_tab[op_code - 1].args[n] & process->decoded[n]))
				return (0);
			if (process->decoded[n] & T_REG)
				process->arg_size[n] = 1;
			else if (process->decoded[n] & T_IND)
				process->arg_size[n] = 2;
			else if (process->decoded[n] & T_DIR)
				process->arg_size[n] = (g_op_tab[op_code - 1].index ? 2 : 4);
			n++;
		}
		n = -1;									//	Debug
		while (++n < 3)							//	Debug
			pf("Prm %d %s size %d\n", n, (process->decoded[n] == T_REG ? "T_REG" : (process->decoded[n] == T_DIR ? "T_DIR" : (process->decoded[n] ? "T_IND" : ""))), process->arg_size[n]);
		return (1);
	}
	return (0);
}
