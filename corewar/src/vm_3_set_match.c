/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_3_set_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:37:05 by edebise           #+#    #+#             */
/*   Updated: 2018/02/21 16:12:01 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_print_arena(t_all *all, t_process *pro)
{
	int x;
	int y;

	pf("{X}{W}{bk}   ");
	x = -1;
	while (++x < 64)
		pf(x < 63 ? " %02d" : " %02d   \n", x);
	y = 0;
	while (y < 64)
	{
		pf("{W}{bk}%02d {0}", y);
		x = 0;
		while (x < 64)
		{
			pf(all->color[y * 64 + x] >= 0 ?
						all->champ[(int)all->color[y * 64 + x]].color : "{0}");
			pf(" %02hhx", all->arena[y * 64 + x]);
			x++;
		}
		if (y > 0 && y < 17 && pro)
			pf(" {W}  {0}\tr%02d %08x\n", y, pro->r[y]);
		else
			pf(" {W}  {0}\n");
		y++;
	}
	pf("{W}%198s{0}\n", "");
}

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
//	all->op_fn[12] = &vm_fork;
	all->op_fn[13] = &vm_lld;
	all->op_fn[14] = &vm_lldi;
//	all->op_fn[15] = &vm_lfork;
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

	delta = MEM_SIZE  / all->nb_champ;
//	pf("Delta {y}%d\n{0}", delta);
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
	vm_set_op_function(all);
	vm_print_arena(all, 0);			//	Debug
}
