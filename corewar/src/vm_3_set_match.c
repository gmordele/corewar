/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_3_set_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:37:05 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:52:03 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_set_op_function()
**	initialize op_fn with op function ptr
*/

void	vm_set_op_function(t_all *all)
{
	all->op_fn[1] = &vm_live;
	all->op_fn[2] = &vm_ld;
	all->op_fn[3] = &vm_st;
	all->op_fn[4] = &vm_add;
	all->op_fn[5] = &vm_sub;
	all->op_fn[6] = &vm_and;
	all->op_fn[7] = &vm_or;
	all->op_fn[8] = &vm_xor;
	all->op_fn[9] = &vm_zjmp;
	all->op_fn[10] = &vm_ldi;
	all->op_fn[11] = &vm_sti;
	all->op_fn[12] = &vm_fork;
	all->op_fn[13] = &vm_lld;
	all->op_fn[14] = &vm_lldi;
	all->op_fn[15] = &vm_lfork;
	all->op_fn[16] = &vm_aff;
}

/*
**	vm_set_match()
**	initialize memory (arena, color) and process_list
*/

void	vm_set_match(t_all *all)
{
	int	delta;
	int	n;

	delta = MEM_SIZE / all->nb_champ;
	ft_memset(all->color, -1, MEM_SIZE);
	n = 0;
	while (n < all->nb_champ)
	{
		ft_memcpy(all->arena + (delta * n), all->champ[n].prog,
													all->champ[n].prog_size);
		ft_memset(all->color + (delta * n), n, all->champ[n].prog_size);
		vm_add_pro_frt(&all->process_list, vm_new_pro(all, NULL, delta * n));
		all->process_list->r[1] = all->champ[n].nb;
		n++;
	}
	all->last_live = all->nb_champ - 1;
	all->cycle_to_die = CYCLE_TO_DIE;
	vm_set_op_function(all);
}

/*
**	vm_print_dump()
**	print arena memory on stdout at 'all->dump' cycle
*/

void	vm_print_dump(t_all *all)
{
	int n;

	n = 0;
	while (n < MEM_SIZE)
	{
		pf("0x%04x : %02hhx ", n, all->arena[n]);
		while (++n % 64)
			pf("%02hhx ", all->arena[n]);
		pf("\n");
	}
}

/*
**	vm_print_winner()
**	print winner or dump on stdout
*/

void	vm_print_winner(t_all *all)
{
	int n;

	n = 0;
	pf("Introducing contestants...\n");
	while (n < all->nb_champ)
	{
		pf("* Player %d, weighing %d bytes,", n + 1, all->champ[n].prog_size);
		pf(" \"%s\" ", all->champ[n].header.prog_name);
		pf("(\"%s\") !\n", all->champ[n++].header.comment);
	}
	n = 0;
	if (all->flag & DUMP && all->cycle == all->dump && all->process_list)
		vm_print_dump(all);
	else
	{
		if (all->flag & AFF)
			pf("Aff:%s\n", all->aff_str);
		pf("Contestant %d, \"%s\", ", all->last_live + 1,
			all->champ[all->last_live].header.prog_name, all->cycle);
		pf("has won in %d cycles !\n", all->cycle);
	}
}
