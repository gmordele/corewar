/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_5_mem_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:04:04 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:24:07 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_ajust_addr()
**	correct addr if it is negative or bigger than MEM_SIZE
*/

int		vm_ajust_addr(long addr)
{
	while (addr < 0)
		addr += MEM_SIZE;
	return ((int)(addr % MEM_SIZE));
}

/*
**	vm_get_mem()
**	return an int filled with 'size' byte (max 4)
**	endian is reversed in reading
*/

int		vm_get_mem(t_all *all, int addr, int size)
{
	int		out;
	int		n;

	out = 0;
	n = 0;
	while (size-- > 0)
		((char*)&out)[n++] = all->arena[vm_ajust_addr(addr + size)];
	return (n == 2 ? (short)out : out);
}

/*
**	vm_put_mem()
**	write 'size' byte of 'value' in 'all->arena'
**	endian is reversed in writing
*/

void	vm_put_mem(t_all *all, int value, int addr, int size)
{
	int		n;

	n = 0;
	while (size-- > 0)
		all->arena[vm_ajust_addr(addr + size)] = ((char*)&value)[n++];
}

/*
**	vm_put_color()
**	set 'size' byte in 'all->color' with all->color[process->pc]
*/

void	vm_put_color(t_all *all, t_process *process, int addr, int size)
{
	char color;

	color = all->color[vm_ajust_addr(process->pc)];
	while (size-- > 0)
		all->color[vm_ajust_addr(addr + size)] = color;
}
