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

void	vm_print_process(t_all *all, t_process *pro, t_process *current, int y)
{
	int n;

	n = 10;
	while (pf(" ") && pro && n--)
	{
		if (y == 1)
			pf(" %spc_%-2d%5d {0} ", all->color[vm_ajust_addr(pro->pc)] >= 0 ? all->champ[(int)all->color[pro->pc % MEM_SIZE]].color : "", pro->nb, vm_ajust_addr(pro->pc));
		else if (y == 2)
			pf("(%sy %02d, x %02d{0}) ", all->color[vm_ajust_addr(pro->pc)] >= 0 ? all->champ[(int)all->color[pro->pc % MEM_SIZE]].color : "", vm_ajust_addr(pro->pc) / 64, vm_ajust_addr(pro->pc) % 64);
		else if (y == 3)
			pf(pro == current ? "{B} %-11.11s{0} " : "{R} %-11.11s{0} ", pro->op);
		else if (y == 4)
			pf(" cycle %4d  ", pro->cycle);
		else if (y == 5)
			pf(" carry %4d  ", pro->carry);
		else if (y > 5 && y < 22)
			pf("r%02x %08x ", y - 5, pro->r[y - 5]);
		pro = pro->next;
	}
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
		tab[x++] = vm_ajust_addr(tmp->pc);
		tmp = tmp->next;
	}
	tab[x] = -1;

	pf("{X}{W}{bk}   ");
	x = -1;
	while (++x < 64)
		pf(x < 63 ? " %02d" : " %02d   {0}", x);
	pf("  Cycle %5d,  Cycle_to_die %4d,  Cycle_before_die %4d,  Nb_live %2d,  Nb_check %2d,  Last_live %s\n", all->cycle, CYCLE_TO_DIE - all->cycle_delta, all->cycle_to_die, all->nb_live, all->nb_checks, all->last_live ? all->champ[all->last_live - 1].header.prog_name : "");
/*	if (pro || !pf("\n"))
	{
		if (all->color[pro->pc % MEM_SIZE] >= 0)
			pf(all->champ[(int)all->color[pro->pc % MEM_SIZE]].color);
		pf("\tpc%-2d %-4d (y %d, x %d)\t{y}op %s{0}\n", pro->nb, pro->pc, pro->pc / 64, pro->pc % 64, pro->op);
	}*/
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
				pf(pro && vm_ajust_addr(pro->pc) == (y * 64 + x) ? "{B}" : "{R}");
			pf("%02hhx{0} ", all->arena[y * 64 + x]);
			x++;
		}
		pf("{W}  {0}\t");
	//	if (y == 0 && all->last_live)
	//		pf("Last_live %s%s{0}", all->champ[all->last_live - 1].color,all->champ[all->last_live - 1].header.prog_name);
	//	else if (y > 0 && y < 17 && pro)
	//		pf("r%02d %08x", y, pro->r[y]);
		pro && y >= 0 && y < 22 ? vm_print_process(all, all->process_list, pro, y) : 0;
		pf("\n");
		y++;
	}
	pf("{W}%198s{0}\n", "");
	write(1, all->aff_str, all->aff_str_size);
	all->flag ? 0 : get_next_line(0, &all->gnl);			//	Debug
}

/*
**	vm_print_dump()
**	print arena on stdout at 'all->dump' cycle
*/

void	vm_print_dump(t_all *all)
{
	int n;

	n = 0;
//	pf("{y}vm_print_dump at %d cycle...\n{0}", all->cycle);		//	Debug
	pf("Introducing contestants...\n");
	while (n < all->nb_champ)
	{
		pf("* Player %d, weighing %d bytes,", n + 1, all->champ[n].prog_size);
		pf(" \"%s\" ", all->champ[n].header.prog_name);
		pf("(\"%s\") !\n", all->champ[n++].header.comment);
	}
	if (all->cycle != all->dump)
		pf("dump %d, {y}cycle %d, cycle_to_die %d.{0}\n", all->dump, all->cycle, CYCLE_TO_DIE - all->cycle_delta);	//	Debug
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
//	all->flag ? 0 : vm_print_arena(all, 0);			//	Debug
}
