/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_6_ajust_addr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 02:21:50 by proso             #+#    #+#             */
/*   Updated: 2018/02/17 04:46:52 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
** Cette fonction prends un int en paramètre, aui représente une adresse.
** Si l'int est dépasse MEM_SIZE ou s'il est négatif alors la fonction
** l'ajuste pour qu'il soit correct.
*/

int		vm_ajust_addr(int addr)
{
	int		new_addr;

	new_addr = addr;
	while (new_addr < 0)
		new_addr += MEM_SIZE;
	while (new_addr > MEM_SIZE)
		new_addr -= MEM_SIZE;
	return (new_addr);
}

/*
** Cette fonction permet de convertir un paramètre écris de base sur plusieurs
** octets en un paramètre écris sur un seul int.
*/

int		vm_convert_param(t_all *all, int addr, int size)
{
	int		out;
	int		i;
	char	*ptr_out;

	i = 0;
	ptr_out = (char*)&out;
	while (size)
	{
		ptr_out[i] = all->arena[vm_ajust_addr(addr + size - 1)];
		size--;
		i++;
	}
	return (out);
}
