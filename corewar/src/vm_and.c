/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:45:07 by edebise           #+#    #+#             */
/*   Updated: 2018/02/17 15:45:11 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	A modifier
**	vm_decode_byte() ok
**	vm_check_params devrait remplacer le type d'argument dans 'decoded' par la longueur des params
**	vm_get_params pourrait alors placer les octets dans chaque int de 'param'
*/

void	vm_get_params(char *decoded, int *param)
{
	ft_bzero(param, sizeof(int) * 3);

}

void	vm_set_params_ptr(char *decoded, char **ptr)
{
	int n;

	pf("Set params\n");
	n = 0;
	while (n < 3 && ptr[n])
	{
		if (decoded[n] == REG_CODE)
			ptr[n + 1] = ptr[n] + 1;
		else if (decoded[n] == IND_CODE)
			ptr[n + 1] = ptr[n] + (decoded[3] ? 2 : 4);
		else if (decoded[n] == DIR_CODE)
			ptr[n + 1] = ptr[n] + 4;
		n++;
	}
}

int		vm_check_params(int instruction, char *decoded)
{
	extern t_op	g_op_tab;
	t_op		*tab;
	int			n;

	pf("Check params\n");
	tab = &g_op_tab;
	while (tab->opcode && tab->opcode != instruction)
		tab++;
	if (tab->opcode)
	{
		n = 0;
		while (n < 3 && tab->args[n])
		{
			if (!(tab->args[n] & decoded[n]))
				return (0);
			// else : remplacer T_ARG par le nb d'octet du param
			n++;
		}
		decoded[3] = (char)tab->index;
		return (1);
	}
	return (0);
}

void	vm_decode_byte(char encoded, char *decoded)
{
	int n;

	pf("Decode byte\n");
	ft_bzero(decoded, sizeof(char) * 4);
	n = 3;
	while (n-- > 0)
	{
		encoded >>= 2;
		if ((encoded & 0x3) == REG_CODE)
			decoded[n] = T_REG;
		else if ((encoded & 0x3) == DIR_CODE)
			decoded[n] = T_DIR;
		else if ((encoded & 0x3) == IND_CODE)
			decoded[n] = T_IND;
	}
	n = -1;
	while (++n < 3)
		pf("Prm %d %s\n", n, (decoded[n] ? (decoded[n] == T_REG ? "T_REG" : (decoded[n] == T_DIR ? "T_DIR" : "T_IND")) : ""));
}

int		vm_and(t_all *all, t_process *process)
{
	int		*param_size[3];
	char	decoded[4];
	int		param[3];

	pf("And\n");
	ft_bzero(ptr, sizeof(char*) * 5);
	vm_decode_byte(all->arena[process->pc + 1], decoded);
	if (vm_check_params(6, decoded))
	{
		pf("Params valides\n");
		vm_
	}
	return (0);
}
