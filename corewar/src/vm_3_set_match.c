/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_3_set_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:37:05 by edebise           #+#    #+#             */
/*   Updated: 2018/02/22 21:44:09 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

int		vm_check_process(int *tab, int address)
{
	int	n = 0;

	while (tab[n] >= 0 && tab[n] != address)
		n++;
	return (tab[n] >= 0);
}

void	vm_print_arena(t_all *all, t_process *pro)
{
	t_process	*tmp;
	int	tab[1000];
	int x;
	int y;

	tmp = all->process_list;
	x = 0;
	while (tmp)
	{
		tab[x++] = vm_correct_addr(tmp->pc);
		tmp = tmp->next;
	}
	tab[x] = -1;

	pf("{X}{W}{bk}   ");
	x = -1;
	while (++x < 64)
		pf(x < 63 ? " %02d" : " %02d   {0}\tCycle %d", x, all->cycle);
	if (pro || !pf("\n"))
	{
		if (all->color[pro->pc % MEM_SIZE] >= 0)
			pf(all->champ[(int)all->color[pro->pc % MEM_SIZE]].color);
		pf("\tpc %-4d (y %d, x %d)\t{y}op %s{0}\n", pro->pc, pro->pc / 64, pro->pc % 64, pro->op);
	}
	y = 0;
	while (y < 64)
	{
		pf("{W}{bk}%02d {0} ", y);
		x = 0;
		while (x < 64)
		{
			if (all->color[y * 64 + x] >= 0)
				pf(all->champ[(int)all->color[y * 64 + x]].color);
			if (vm_check_process(tab, y * 64 + x))
				pf("{R}");
			pf("%02hhx{0} ", all->arena[y * 64 + x]);
			x++;
		}
		pf("{W}  {0}\t");
		if (y == 0 && all->last_live)
			pf("Last_live %s%s{0}", all->champ[all->last_live - 1].color,all->champ[all->last_live - 1].header.prog_name);
		else if (y > 0 && y < 17 && pro)
			pf("r%02d %08x", y, pro->r[y]);
		pf("\n");
		y++;
	}
	pf("{W}%198s{0}\n", "");
	write(1, all->aff_str, all->aff_str_size);
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
